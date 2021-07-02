#include "../include/boson_render_objects.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../stb/stb_image.h"

Mesh bTriangle()
{
    Mesh tri;
    
    tri.vsize       = 3;
    tri.isize       = 3;
    tri.vertices    = (Vertex*)     malloc(3*sizeof(Vertex));
    tri.indices     = (uint32_t*)   malloc(3*sizeof(uint32_t));

    tri.vertices[0] = (Vertex){+0.0f, +0.5f, +0.0f,	    1,0,0,	0,0};
	tri.vertices[1] = (Vertex){+0.5f, -0.5f, +0.0f, 	0,0,1,	0,0};
	tri.vertices[2] = (Vertex){-0.5f, -0.5f, +0.0f, 	0,1,0,	0,0};

    size_t i_indices[3] = {0, 1, 2};
    memcpy((void*)tri.indices, (void*)i_indices, sizeof(i_indices));

    return tri;
}

Mesh bQuad() 
{
	Mesh quad;

    quad.vsize          = 4;
    quad.isize          = 6;
    quad.vertices       = (Vertex*)     malloc(4*sizeof(Vertex));
	quad.indices        = (int*)        malloc(6*sizeof(int));
	
	quad.vertices[0]    = (Vertex){-0.5f, +0.5f, +0.0f,     1,0,0,	0,1};
	quad.vertices[1]    = (Vertex){-0.5f, -0.5f, +0.0f, 	0,0,1,	0,0};
	quad.vertices[2]    = (Vertex){+0.5f, -0.5f, +0.0f, 	0,1,0,	1,0};
	quad.vertices[3]    = (Vertex){+0.5f, +0.5f, +0.0f, 	0,1,0,	1,1};
	
    int     i_indices[] = {	0, 1, 2, 
						    2, 3, 0	    };
    memcpy((void*)quad.indices, (void*)i_indices, sizeof(i_indices));

	return quad;
}

Mesh bCube()
{
    Mesh cube;
	
    cube.vsize          = 8;
    cube.isize          = 72;
    cube.vertices       = (Vertex*) malloc(8*sizeof(Vertex));
    cube.indices        = (int*)    malloc(72*sizeof(int));

	cube.vertices[0]	= (Vertex){-0.5f, +0.5f, +0.5f,	1,0,0,	0,1};
	cube.vertices[1]	= (Vertex){-0.5f, -0.5f, +0.5f,	0,1,0,	0,0};
	cube.vertices[2]	= (Vertex){+0.5f, -0.5f, +0.5f,	0,0,1,	1,0};
	cube.vertices[3]	= (Vertex){+0.5f, +0.5f, +0.5f,	1,0,0,	1,1};
	cube.vertices[4]	= (Vertex){-0.5f, +0.5f, -0.5f,	0,1,0,	0,1};
	cube.vertices[5]	= (Vertex){-0.5f, -0.5f, -0.5f,	0,0,1,	0,0};
	cube.vertices[6]	= (Vertex){+0.5f, -0.5f, -0.5f,	1,0,0,	1,0};
	cube.vertices[7]	= (Vertex){+0.5f, +0.5f, -0.5f,	0,1,0,	1,1};
	
	int i_indices[] =   {	0, 1, 2, // front
						    2, 3, 0,
    
						    0, 1, 5, // left
						    5, 4, 0,
    
						    0, 3, 7, // top
						    7, 4, 0,
    
						    3, 2, 6, // right
						    6, 7, 3,
    
						    1, 2, 6, // bottom 
						    6, 5, 1,
    
						    5, 6, 7, // back
						    7, 4, 5	};
    memcpy((void*)cube.indices, (void*)i_indices, sizeof(i_indices));
    return cube;
}

Transform bInitTransform()
{
    return (Transform){
        MAT4F_IDENTITY,
        MAT4F_IDENTITY,
        MAT4F_IDENTITY
    };
}

Transform bCreateTransform(vec3f position, quatf orientation)
{
    return (Transform){
        MAT4F_IDENTITY,
        MAT4F_IDENTITY,
        MAT4F_IDENTITY,
        position,
        orientation
    };
}

Camera bInitCamera()
{
    return (Camera){
        MAT4F_IDENTITY,
        MAT4F_IDENTITY,
        MAT4F_IDENTITY,
        (vec3f){0, 0, -1},
        QUATF_IDENTITY,
        0,
        0,
        0
    };
}

void bGenerateMesh(Mesh * m)
{
    glGenVertexArrays(1, &(m->VAO));
    glGenBuffers(1, &(m->VBO));
    glGenBuffers(1, &(m->EBO));
    
    glBindVertexArray(m->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m->VBO);
    glBufferData(GL_ARRAY_BUFFER, m->vsize*sizeof(Vertex), m->fvertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->isize*sizeof(int), m->indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
			
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)12);
	glEnableVertexAttribArray(1);
			
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*)24);
	glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void bDestroyMesh(Mesh * m)
{
    if (m->vertices != NULL)
        free(m->vertices);
    if (m->indices != NULL)
        free(m->indices);
    glDeleteVertexArrays(1, &(m->VAO));
    glDeleteBuffers(1, &(m->VBO));
    glDeleteBuffers(1, &(m->EBO));
}

void bDestroyShader(Shader s)
{
    glDeleteProgram(s);
}

bool bShaderErrorCheck(unsigned int*, GLenum);

bShaderError bCompileShader(String * src, int * ID)
{
    glShaderSource(*ID, 1, &src->c_str, NULL);
    glCompileShader(*ID);

    int     success;
    char    info_log[512];

    glGetShaderiv(*ID, GL_COMPILE_STATUS, &success);
    if (!bShaderErrorCheck(ID, GL_COMPILE_STATUS))
        return SHADER_COMPILE_FAIL;

    return SHADER_OK;
}

bool bShaderErrorCheck(unsigned int * ID, GLenum status)
{
    int     success;
    char    info_log[512];
    
    switch (status)
    {
        case GL_COMPILE_STATUS: 
            glGetShaderiv(*ID, status, &success);
            if (!success)
            {
                glGetShaderInfoLog(*ID, 512, NULL, info_log);
                fprintf(stderr, "%s\n", info_log);
                return false;
            }    
        break;
        case GL_LINK_STATUS:
            glGetProgramiv(*ID, status, &success);
            if (!success)
            {
                glGetShaderInfoLog(*ID, 512, NULL, info_log);
                fprintf(stderr, "%s\n", info_log);
                return false;
            }    
        break;
    }

    return true;
}

bShaderError bLoadShaders(const char * filepath, Shader * shader)
{
    String  vsh     = bNewString(filepath),
            fsh     = bNewString(filepath),
            v_src,
            f_src;
    
    bStrAppend(&vsh, ".vsh");
    bStrAppend(&fsh, ".fsh");

    v_src = bLoadCharStream(vsh.c_str);
    f_src = bLoadCharStream(fsh.c_str);

    if (v_src.c_str == NULL || f_src.c_str == NULL)
        return SHADER_SRC_FAIL;

    bDestroyString(&vsh); //printf("%s\n", v_src.c_str);
    bDestroyString(&fsh); //printf("%s\n", f_src.c_str);

    unsigned int    vsh_ID = glCreateShader(GL_VERTEX_SHADER),
                    fsh_ID = glCreateShader(GL_FRAGMENT_SHADER);

    if (bCompileShader(&v_src, &vsh_ID) == SHADER_COMPILE_FAIL)
        return SHADER_VSH_ERROR;
    if (bCompileShader(&f_src, &fsh_ID) == SHADER_COMPILE_FAIL)
        return SHADER_FSH_ERROR;

    *shader = glCreateProgram();
    glAttachShader(*shader, vsh_ID);    
    glAttachShader(*shader, fsh_ID);
    glLinkProgram(*shader);

    if (!bShaderErrorCheck(shader, GL_LINK_STATUS))
        return SHADER_LINK_ERROR;

    glDeleteProgram(vsh_ID);
    glDeleteProgram(fsh_ID);

    bDestroyString(&v_src);
    bDestroyString(&f_src);

    return SHADER_OK;
}

void bSetTextureOptions(uint16_t texID, uint16_t wrap, uint16_t filter)
{
    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}

void bGenerateTexture2D(Texture2D * tex)
{
    static int index = 0;
    tex->index = ++index;   //  TO-DO: this breaks when destroying a texture,
                            //  consider replacing this with a resources list
                            //  to handle all assets, including meshes, transforms, etc.
 
    glGenTextures(1, (GLuint*)&(tex->ID));
    glBindTexture(GL_TEXTURE_2D, tex->ID);
    bSetTextureOptions(tex->ID, GL_REPEAT, GL_NEAREST);

    glTexImage2D(   GL_TEXTURE_2D, 
                    0, 
                    GL_RGB, 
                    tex->w, 
                    tex->h, 
                    0, 
                    GL_RGB, 
                    GL_UNSIGNED_BYTE, 
                    (void*)tex->data);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex->data);
}

void bLoadTexture2DFromFile(const char * filepath, Texture2D * tex)
{
    tex->data   =   stbi_load(  filepath, 
                                (int*)&(tex->w), 
                                (int*)&(tex->h), 
                                (int*)&(tex->ch), 
                                0);

    if (tex->data == NULL)
    {
        fprintf(stderr, "error: failed to load texture from %s\n", filepath);
        return;
    }
    
    bGenerateTexture2D(tex);
}

void bAssignTexture2DToMesh(Texture2D * tex, Mesh * m)
{
    m->texture = tex;
    m->texsize = 1;
}

void bApplyPerspective(Camera * c)
{
    mat4ft_projection(c->ar, 90, 0.1f, 100.f, c->projection.comp);
}

void bApplyView(vec3f to, Camera * c)
{
    //quatf_to_look_mat4f(c->position.c, c->orientation.c, c->view.comp);
    mat4f_look_at(c->position.c, to.c, c->view.comp);
}

void bApplyTransform(Transform * t, Camera * c)
{
    // Apply position and rotation
    mat4f_translate(t->position.c, t->translation.comp);
    quatf_to_mat4f(t->orientation.c, t->rotation.comp);
    
    // Apply these operations to the model matrix
    c->model =  mat4f_mul_new(  t->translation.comp,
                mat4f_mul_new(  t->rotation.comp,
                                t->scale.comp   ).comp);
}

void bPassMVP(Shader s, Camera * c)
{
    setUniformMat4f(&c->model, s, "model");
    setUniformMat4f(&c->view, s, "view");
    setUniformMat4f(&c->projection, s, "projection");
}

void bRenderMesh(Mesh * m, Transform * t, Camera * c)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    bApplyTransform(t, c);
    bPassMVP(m->material, c);

    if (m->texsize >= 1)
    {
        //setUniformi(m->texture->ID, (m->material), "albedo");
        glBindTexture(GL_TEXTURE_2D, m->texture->ID);
    }
    glUseProgram(m->material);
    glBindVertexArray(m->VAO);

    glDrawElements(GL_TRIANGLES, m->isize, GL_UNSIGNED_INT, 0);
}

void bRenderMeshes(Mesh * m, Transform * t, size_t count, Camera * c)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (size_t i = 0; i < count; i++)
    {
        bApplyTransform(&t[i], c);
        bPassMVP(m[i].material, c);

        if (m[i].texsize >= 1)
        {
            glActiveTexture(GL_TEXTURE0 + m[i].texture->index);
            glBindTexture(GL_TEXTURE_2D, m[i].texture->ID);

            setUniformi(m[i].texture->ID, (m[i].material), "albedo");
        }
        glUseProgram(m[0].material);
        glBindVertexArray(m[i].VAO);

        glDrawElements(GL_TRIANGLES, m[i].isize, GL_UNSIGNED_INT, 0);
    }
}

void setUniformi(int value, Shader s, const char * uniform_name) 
{
	int ID = glGetUniformLocation(s, uniform_name);
	glUniform1i(ID, value);
}

void setUniformf(float value, Shader s, const char * uniform_name) 
{
	int ID = glGetUniformLocation(s, uniform_name);
	glUniform1f(ID, value);
}

void setUniformVec2f(vec2f * value, Shader s, const char * uniform_name) 
{
	int ID = glGetUniformLocation(s, uniform_name);
	glUniform2f(ID, value->x, value->y);
}

void setUniformVec3f(vec3f * value, Shader s, const char * uniform_name) 
{
	int ID = glGetUniformLocation(s, uniform_name);
	glUniform3f(ID, value->x, value->y, value->z);
}

void setUniformVec4f(vec4f * value, Shader s, const char * uniform_name) 
{
	int ID = glGetUniformLocation(s, uniform_name);
	glUniform4f(ID, value->x, value->y, value->z, value->w);
}

void setUniformMat2f(mat2f * value, Shader s, const char * uniform_name) 
{
	int ID = glGetUniformLocation(s, uniform_name);
	glUniformMatrix2fv(ID, 1, true, value->m);
}

void setUniformMat3f(mat3f * value, Shader s, const char * uniform_name) 
{
	int ID = glGetUniformLocation(s, uniform_name);
	glUniformMatrix3fv(ID, 1, true, value->comp);
}

void setUniformMat4f(mat4f * value, Shader s, const char * uniform_name) 
{
	int ID = glGetUniformLocation(s, uniform_name);
	glUniformMatrix4fv(ID, 1, true, value->comp);
}