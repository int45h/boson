#pragma once
/*
    boson_render_objects.h: Includes everything needed to render objects using shaders
*/

#include "../../glm_lite/glm/include/vec2f.h"
#include "../../glm_lite/glm/include/vec3f.h"
#include "../../glm_lite/glm/include/vec4f.h"
#include "../../glm_lite/glm/include/mat2f.h"
#include "../../glm_lite/glm/include/mat3f.h"
#include "../../glm_lite/glm/include/mat4f.h"
#include "../../glm_lite/glm/include/quatf.h"

#include "../../io/include/boson_io.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include <GL/glew.h>
#include <GL/glu.h>

#include <GL/gl.h>

typedef enum bShaderError
{
    SHADER_OK           = 0,
    SHADER_SRC_FAIL     = -1,
    SHADER_COMPILE_FAIL = -2,
    SHADER_VSH_ERROR    = -3,
    SHADER_FSH_ERROR    = -4,
    SHADER_LINK_ERROR   = -5
}
bShaderError;

/* Here, a vertex is defined in 8 bytes: 3 for position, 3 for normals, and 2 for color */
typedef union Vertex
{
    struct  {float x, y, z, r, g, b, u, v;};
    struct  {vec3f xyz, rgb; vec2f uv;};
    float   c[8];
}
Vertex;

/* Texture definition (2D) */
typedef struct Texture2D
{
    uint8_t *       data;       // Raw pizel data
    GLuint          ID,         // Texture ID
                    w,          // Width (px)
                    h,          // Height (px)
                    ch,         // Channels
                    size;       // Size (bytes)
    size_t          index;      // Texture index
    const char *    uniform;    // Uniform ID (for shader)
}
Texture2D;

#define TEXTURE2D_NULL  (Texture2D){    NULL,\
                                        0,\
                                        0,\
                                        0,\
                                        0,\
                                        0\
                                        }   

/* Shader program (The struct is a bit unnecessary but there for completeness) */
typedef unsigned int Shader;

/* Really, a mesh is just an array of vertices and indices */
typedef struct Mesh
{
    union   {   Vertex* vertices;    
                float*  fvertices;  };
    int*                indices;
    int                 VAO,
                        VBO,
                        EBO,
                        vsize,
                        isize;
    Texture2D*          texture;
    Shader              material;
    size_t              texsize;
}
Mesh;

/* And a model is really just an array of meshes */
typedef struct Model
{
    Mesh*   meshes;
    size_t  count;
}
Model;

/* Transform object */
typedef struct Transform
{
    mat4f   translation,
            rotation,
            scale;
    vec3f   position;
    quatf   orientation;
}
Transform;

/* Camera object */
typedef struct Camera
{
    mat4f   projection,
            view,
            model;          // MVP Matrix
    vec3f   position;       // Position
    quatf   orientation;    // Orientation

    size_t  width,          // Width + Height of render
            height;
    float   ar;             // Aspect ratio
}
Camera;

Transform   bInitTransform();
Transform   bCreateTransform(vec3f position, quatf orientation);

Camera      bInitCamera();

Mesh bTriangle();
Mesh bQuad();
Mesh bCube();

bShaderError bCompileShader(String * src, int * ID);
bShaderError bLoadShaders(const char * filepath, Shader * shader);

bool bShaderErrorCheck(unsigned int*, GLenum);
bool bShaderErrorCheck(unsigned int * ID, GLenum status);

void bGenerateMesh(Mesh * m);
void bDestroyMesh(Mesh * m);
void bDestroyShader(Shader s);

void bSetTextureOptions(uint16_t texID, uint16_t wrap, uint16_t filter);
void bGenerateTexture2D(Texture2D * tex);
void bLoadTexture2DFromFile(const char * filepath, Texture2D * tex);
void bAssignTexture2DToMesh(Texture2D * tex, Mesh * m);
void bApplyPerspective(Camera * c);
void bApplyView(vec3f to, Camera * c);
void bApplyTransform(Transform * t, Camera * c);

void bPassMVP(Shader s, Camera * c);
void bRenderMesh(Mesh * m, Transform * t, Camera * c);
void bRenderMeshes(Mesh * m, Transform * t, size_t count, Camera * c);

void setUniformi(int value, Shader s, const char * uniform_name);
void setUniformf(float value, Shader s, const char * uniform_name);
void setUniformVec2f(vec2f * value, Shader s, const char * uniform_name);
void setUniformVec3f(vec3f * value, Shader s, const char * uniform_name);
void setUniformVec4f(vec4f * value, Shader s, const char * uniform_name);
void setUniformMat2f(mat2f * value, Shader s, const char * uniform_name);
void setUniformMat3f(mat3f * value, Shader s, const char * uniform_name);
void setUniformMat4f(mat4f * value, Shader s, const char * uniform_name);