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
    B_NONE,
    B_WINDOW_RESIZE,
    B_KEYDOWN,
    B_EXIT
}
bEvents;

typedef struct Window
{
    SDL_Window*     w;
    SDL_Renderer*   r;
    SDL_Texture*    t;
    SDL_Event       e;
    SDL_GLContext   wContext;
    
    const char * title;    
    size_t  width, 
            height;
    float   ar;
}
Window;

char        bGetKeycode(Window * w);

void        bInitRenderer(int major, int minor);
void        bQuit();

Window      bCreateWindow(size_t w, size_t h, const char * title);
void        bUpdateWindow(Window * w);
void        bPushFrameBuffer(const uint32_t * fb, Window * w);
void        bRefreshWindow(Window * w);

void        bResizeWindow(Window * win, size_t w, size_t h);
void        bDestroyWindow(Window * w);
bEvents     bPollEvent(Window * w);

void        bTick(void);