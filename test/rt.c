#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include "../renderer/include/boson_window.h"
#include "../io/include/boson_io.h"
#include "../glm_lite/glm.h"

#define tolower(x) x & 0x20

char *
init_progress_bar(size_t size);

void
show_progress(float percent, char * bar, size_t size);

float
randf()
{
    return (float)rand() / (RAND_MAX);
}

float
randf_ranged(float min, float max)
{
    return min + (max-min) * (float)rand() / (RAND_MAX);
}

uint8_t
near_zero(float * input)
{
    return ((fabs(input[0]) < 1e-8) && 
            (fabs(input[1]) < 1e-8) && 
            (fabs(input[2]) < 1e-8));
}

typedef struct ray3f
{
    vec3f   origin, 
            dest;
    float   length;
}
ray3f;

vec3f
rayf_at_new(ray3f r, float t)
{
    return (vec3f){ r.origin.c[0] + t*r.dest.c[0],
                    r.origin.c[1] + t*r.dest.c[1],
                    r.origin.c[2] + t*r.dest.c[2]};
}

typedef enum OBJ_TYPES
{
    SPHERE,
    PLANE,
    BOX,
    POLYGON
}
OBJ_TYPES;

typedef struct object
{
    OBJ_TYPES   type;
    vec3f       center,
                albedo;
    float       size;
}
object;

#define WORLD_BLOCK_SIZE 1024

typedef struct world
{
    object *    objects;
    size_t      count,
                max_size;
}
world;

world
create_world(int max_size)
{
    return (world){ malloc(max_size * sizeof(object)),
                    0,
                    max_size    };
}

void
add_object(world * w, OBJ_TYPES type, vec3f center, vec3f color, float size)
{
    if (w->count++ > w->max_size)
    {
        w->max_size += WORLD_BLOCK_SIZE;
        w->objects = realloc((void*)w->objects, w->max_size * sizeof(object));
    }
    w->objects[w->count-1] = (object){  type,
                                        center,
                                        color,
                                        size};
}

void
destroy_world(world * w)
{
    if (w->objects != NULL)
        free(w->objects);
    w->count = w->max_size = 0;
}

vec3f
unit_random_new()
{
    vec3f rnd = (vec3f){randf_ranged(-1, 1),
                        randf_ranged(-1, 1),
                        randf_ranged(-1, 1)    };
    return vec3f_normalize_new(rnd.c);
}

void
gammavf(float * in)
{
    in[0] = sqrtf(in[0]);
    in[1] = sqrtf(in[1]);
    in[2] = sqrtf(in[2]);
}

void
rayf_at(float o[3], float d[3], float t, float dest[3])
{
    dest[0] = o[0]+t*d[0];
    dest[1] = o[1]+t*d[1];
    dest[2] = o[2]+t*d[2];
}

typedef struct camera
{
    size_t  width,
            height;
    float   ar,
            focal_length,
            v_width,
            v_height;

    vec3f   origin;
}
camera;

camera
init_camera(size_t w, 
            size_t h, 
            float v_scale,
            size_t focal_length, 
            vec3f origin)
{
    return (camera){    w,
                        h,
                        (float)w / (float)h,
                        focal_length,
                        v_scale * (float)w / (float)h,
                        v_scale,
                        origin  };
}

typedef struct hit_record
{
    vec3f   hit,
            normal,
            albedo;
    float   root;
}
hit_record;

vec3f
vrgb(float x, float y, float z)
{
    return (vec3f){x, y, z};
}

uint32_t
vec3f_color_to_px(float c[3])
{
    uint8_t R = floor(255.999 * c[0]),
            G = floor(255.999 * c[1]),
            B = floor(255.999 * c[2]);
    return (uint32_t)(R) << 24 | (uint32_t)(G) << 16 | (uint32_t)(B) << 8;
}

ray3f
fire_ray(vec3f origin, vec3f dest)
{
    return (ray3f){ origin,
                    dest};
}

ray3f
fire_ray_from_camera(camera * c, float u, float v)
{
    float   x = (c->v_width * 0.5f),
            y = (c->v_height * 0.5f);
    return (ray3f){ c->origin,
                    (vec3f){(u*c->v_width / c->width) - x,
                            (v*c->v_height / c->height) - y,
                            -1}};
}

uint8_t
hit_sphere( vec3f center, 
            float radius, 
            float t_min, 
            float t_max, 
            ray3f * r, 
            hit_record * rec)
{
    vec3f   sphere_dist = vec3f_sub_new(r->origin.c, center.c);
    float   a           = vec3f_length_squared(r->dest.c),
            b           = vec3f_dot(sphere_dist.c, r->dest.c),
            c           = vec3f_length_squared(sphere_dist.c) - radius*radius,
            desc        = b*b - a*c;
    if (desc < 0)
        return 0;
    float   sqrt_desc = sqrt(desc),
            root = (-b - sqrt_desc) / a;

    if (root < t_min || root > t_max)
    {
        root = (-b + sqrt_desc) / a;
        if (root < t_min || root > t_max)
            return 0;
    }
    rec->root   = root;
    rec->hit    = rayf_at_new(*r, root);
    rec->normal = vec3f_scale_new(  vec3f_sub_new(    
                                        rec->hit.c, 
                                        center.c).c, 
                                    1 / radius);
    vec3f_adds(rec->normal.c, 1, rec->normal.c);
    vec3f_scale(rec->normal.c, 0.5, rec->normal.c);
    return 1;
}

uint8_t
hit_plane(  vec3f center, 
            float size,
            float t_min,
            float t_max,
            ray3f * r,
            hit_record * rec)
{
    uint8_t did_hit = 0;
    float D_n = vec3f_dot(
                    r->dest.c, 
                    (vec3f){0,1,0}.c);
    vec3f plane_normal = (center.y <= 0) ? (vec3f){0,1,0} : (vec3f){0,-1,0};
    if (D_n > 1e-6)
    {
        float PO_n = vec3f_dot(
                        vec3f_sub_new(r->origin.c, center.c).c,
                        plane_normal.c);
        rec->root   = PO_n / D_n;
        if (rec->root >= 0)
        {
            did_hit     = 1;
            rec->normal = plane_normal;
            rec->hit    = rayf_at_new(*r, rec->root);
        }
    }
    return did_hit;
}

uint8_t 
hit_object(world * w, float t_min, float t_max, ray3f * r, hit_record * rec)
{
    uint8_t hit         = 0,
            current_hit = 0;
    float   closest     = t_max;
    
    hit_record tmp;

    for (size_t i = 0; i < w->count; i++)
    {
        switch (w->objects[i].type)
        {
            case SPHERE:
            if (current_hit = hit_sphere(   w->objects[i].center, 
                                            w->objects[i].size,
                                            t_min,
                                            closest,
                                            r,
                                            &tmp))
            {
                hit = 1;
                closest = tmp.root;
                *rec    = tmp;
                rec->albedo = w->objects[i].albedo;
            }
            break;
            case PLANE:
            if (current_hit = hit_plane(    w->objects[i].center, 
                                            w->objects[i].size,
                                            t_min,
                                            closest,
                                            r,
                                            &tmp))
            {
                hit = 1;
                closest = tmp.root;
                *rec    = tmp;
                rec->albedo = w->objects[i].albedo;
            }
            break;
        }
    }
    return hit;
}

uint8_t 
lambert_diffuse(ray3f * r,
                hit_record * rec)
{
    vec3f dest = vec3f_add_new(rec->normal.c, unit_random_new().c);
    if (near_zero(dest.c))
        dest = rec->normal;
    
    *r = (ray3f){
        rec->hit,
        dest
    };
    return 1;
}

uint8_t
lambert_reflectance(ray3f * r,
                    hit_record * rec,
                    float fuzz)
{
    vec3f dest = vec3f_reflect_new(
                    r->dest.c,
                    rec->normal.c
    );
    vec3f_add(
        dest.c, 
        vec3f_scale_new(unit_random_new().c, fuzz).c,
        dest.c
    );
    *r = (ray3f){
        rec->hit,
        dest
    };
    return (vec3f_dot(dest.c, rec->normal.c) > 0);
}

vec3f
ray_color(  ray3f * r,
            world * w,
            int depth)
{
    hit_record rec;
    if (depth <= 0)
        return (vec3f){0,0,0};
    
    float   factor  = vec3f_normalize_new(r->dest.c).y,
            fuzz    = 0.25f;
    vec3f   attenuation;

    if (hit_object(w, 0.00001, 100, r, &rec))
    {
        attenuation = rec.normal;
        float Kd = 0.5;//vec3f_dot(vec3f_normalize_new(r->dest.c).c, rec.normal.c);
        if (lambert_diffuse(r, &rec))
        {
            vec3f next_color = vec3f_scale_new(ray_color(
                r, w, depth-1
            ).c, Kd);
            vec3f_mul(attenuation.c, next_color.c, attenuation.c);
        }
        else
            attenuation = (vec3f){0,0,0};
        return (attenuation);
    }
    
    return (attenuation = vec3f_lerp_new(vrgb(0.5, 0.7, 1.0).c, vrgb(1, 1, 1).c, factor));
}

void 
draw_scene(uint32_t * fb, camera * c, world * w, int spp, int depth)
{
    char * progress_bar = init_progress_bar(32);
    ray3f       r;
    
    for (int y = 0; y < c->height; y++){
    for (int x = 0; x < c->width; x++){
        vec3f   out     = vrgb(0,0,0),
                color   = vrgb(0,0,0);
        
        for (int s = spp; s > 0; s--)
        {
            r       = fire_ray_from_camera( c, 
                                            x+randf_ranged(-1, 1), 
                                            y+randf_ranged(-1, 1));
            color   = ray_color(&r, w, depth);
            
            vec3f_add(color.c, out.c, out.c);
        }
        vec3f_scale(out.c, 1/(float)spp, out.c);
        gammavf(out.c);
        fb[(c->height-1-y)*c->width + x] = vec3f_color_to_px(out.c);
    }
    float progress = (y*c->width) / (float)(c->width*c->height);
    show_progress(progress, progress_bar, 32);
    }
    printf("\n");
    free(progress_bar);
}

void 
usage()
{
    printf("\nUSAGE:\n");
    printf("rt [options]\n\n");
    printf("\t-s, --spp: Samples per pixel. (default=16)\n");
    printf("\t-d, --depth, -b, --bounces: Number of ray bounces. (default=4)\n");
}

int
parse_args(int argc, char ** argv, int * spp, int * depth)
{
    if (argc > 1)
    {
        for (int i = 1; i < argc-1; i++)
        {
            if      (   (strncmp("--spp", argv[i], 5) == 0) || (strncmp("-s", argv[i], 2) == 0))
            {
                if (i+1 >= argc)
                {
                    fprintf(stderr, "error: expected something after argument '%s'\n", argv[i]);
                    usage();
                    return 1;
                }
                else if ((*spp = atoi(argv[i+1])) == 0)
                {
                    fprintf(stderr, "error: invalid argument!\n");
                    usage();
                    return 1;
                }
            }
            else if (   (strncmp("--depth", argv[i], 5) == 0) || (strncmp("-d", argv[i], 2) == 0) || 
                        (strncmp("--bounces", argv[i], 5) == 0) || (strncmp("-b", argv[i], 2) == 0))
            {
                if (i+1 >= argc)
                {
                    fprintf(stderr, "error: expected something after argument '%s'\n", argv[i]);
                    usage();
                    return 1;
                }
                else if ((*depth = atoi(argv[i+1])) == 0)
                {
                    fprintf(stderr, "error: invalid argument!\n");
                    usage();
                    return 1;
                }
            }
        }
    }
    return 0;
}

char *
init_progress_bar(size_t size)
{
    char * bar = malloc((size+3)*sizeof(char));
    bar[0]      = '[';
    bar[size+1] = ']';
    bar[size+2] = '\0';
    for (size_t i = 1; i < size; i++)
        bar[i] = '_';
    return bar;
}

void
show_progress(float percent, char * bar, size_t size)
{
    int progress = mini(floor(percent*size), size);
    for (size_t i = 1; i < progress+1; i++)
        bar[i] = '#';
    printf("\r%s %.2f%% complete", bar, percent*100);
    fflush(stdout);
}

#define ROW_SIZE 12 
bIOError
write_to_ppm(const char * filename, uint32_t * fb, size_t w, size_t h)
{
    size_t      size = ROW_SIZE*w*(h+2),
                row_end;
    bIOError    return_code;
    char        * ppm  = malloc(size*sizeof(char));

    for (size_t i = 0; i < size; i++)
        ppm[i] = ' ';

    row_end         = sprintf(ppm, "P3\n%d %d\n255\n", w, h);
    ppm[row_end] = ' ';

    for (size_t pix = 0; pix < w*h; pix++)
    {
        // Decode pixel
        int R = (fb[pix] & 0xFF000000) >> 24,
            G = (fb[pix] & 0x00FF0000) >> 16,
            B = (fb[pix] & 0x0000FF00) >> 8;
        
        row_end         = sprintf((ppm + ((pix+2)*12)), "%d %d %d\n", R, G, B);
        ppm[(pix+2)*12 + row_end]    = ' ';
    }
    return_code = bWriteCharStream(filename, ppm, size);
    free(ppm);

    return return_code;
}

int 
main(int argc, char ** argv)
{
    srand((unsigned int)time(NULL));
    int spp     = 16,
        depth   = 4;
    int return_code = 0;
    

    if ((return_code = parse_args(argc, argv, &spp, &depth)) != 0)
        return return_code;
    
    bInitRenderer(4, 5);
    Window display = bCreateWindow(640, 480, "Boson RT Test");
    
    uint32_t    *fb     = malloc(display.width*display.height*sizeof(uint32_t));
    camera c = init_camera( display.width, 
                            display.height, 
                            2,
                            1, 
                            (vec3f){0,0,0});
    
    world w = create_world(2);
    add_object(&w, SPHERE, (vec3f){0,0,-5}, vrgb(1,0,0), 2);
    //add_object(&w, PLANE, (vec3f){0,1,-10}, vrgb(1,0,0), 2);
    add_object(&w, SPHERE, (vec3f){0,-102,-9}, vrgb(1,1,0), 100);

    draw_scene(fb, &c, &w, spp, depth);
    bPushFrameBuffer(fb, &display);
    
    uint8_t breakout = 0;
    while(!breakout)
    {
        bRefreshWindow(&display);
        switch(bPollEvent(&display))
        {
            case B_EXIT:
                breakout = 1;
                break;
            case B_KEYDOWN:
                switch (bGetKeycode(&display))
                {
                    case 'r':
                        draw_scene(fb, &c, &w, spp, depth);
                        bPushFrameBuffer(fb, &display);
                        printf("\nRefreshed the screen!\n");
                    break;
                    case 's':
                        if(write_to_ppm("./out.ppm", fb, display.width, display.height) == B_READALL_OK)
                            printf("\nSuccessfully wrote to 'out.ppm'\n");
                    break;
                }
                break;
                //a
            //case B_WINDOW_RESIZE:
            //    bResizeWindow(&display, 
            //                    display.e.window.data1, 
            //                    display.e.window.data2);
            //    c   = init_camera(display.width, display.height, 2, 1, c.origin);
            //    printf("Resized to %dx%d, AR=%f\n", c.width, c.height, c.ar);
            //    fb      = realloc((void*)fb, c.width*c.height*sizeof(uint32_t));
            //    draw_scene(fb, &c, &w, spp, depth);
            //    bPushFrameBuffer(fb, &display);
            break;
        }
    }

    bDestroyWindow(&display);
    destroy_world(&w);
    free(fb);
    bQuit();

    return 0;
}