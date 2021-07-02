#pragma once

/*
    boson_window.h: Window toolkit for the Boson engine
*/

#include <SDL2/SDL.h>

#include <GL/glew.h>
#include <GL/glu.h>

#include <GL/gl.h>

typedef enum bEvents
{
    NONE,
    EXIT
}
bEvents;

typedef struct Window
{
    SDL_Window*     w;
    SDL_Renderer*   r;
    SDL_Event       e;
    SDL_GLContext   wContext;
    
    const char * title;    
    size_t  width, 
            height;
    float   ar;
}
Window;

void        bInitRenderer(int major, int minor);

Window      bCreateWindow(size_t w, size_t h, const char * title);
void        bUpdateWindow(Window * w);

void        bDestroyWindow(Window * w);
bEvents     bPollEvent();

void        bTick(void);