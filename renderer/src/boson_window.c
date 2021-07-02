#include "../include/boson_window.h"

void bInitRenderer(int major, int minor)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Enable depth bit
	glEnable(GL_DEPTH_TEST);
    
    // Debugging
    glEnable(GL_DEBUG_OUTPUT);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0)
    {
        fprintf(stderr, "error: failed to init window: %s\nExiting!\n", SDL_GetError());
        return;
    }
}

void bDestroyWindow(Window * w)
{
    SDL_GL_DeleteContext(w->wContext);
    SDL_DestroyWindow(w->w);
}

Window bCreateWindow(size_t w, size_t h, const char * title)
{
    Window disp;
    disp.w          = SDL_CreateWindow( title, 
                                        SDL_WINDOWPOS_CENTERED, 
                                        SDL_WINDOWPOS_CENTERED, 
                                        w, 
                                        h, 
                                        SDL_WINDOW_OPENGL);
    disp.wContext   = SDL_GL_CreateContext(disp.w);
    disp.ar         = (float)w / (float)h;

    if (disp.wContext == NULL)
    {
        fprintf(stderr, "error: failed to init GL context: %s\n", SDL_GetError());
        bDestroyWindow(&disp);
        return disp;
    }

    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "error: failed to init GLEW\n");
        bDestroyWindow(&disp);
        return disp;
    }

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SDL_GL_SwapWindow(disp.w);

    return disp;
}

void bUpdateWindow(Window * w)
{
    SDL_GL_SwapWindow(w->w);
}

bEvents bPollEvent(Window * w)
{
    if (SDL_PollEvent(&w->e) != 0)
    {
        switch (w->e.type)
        {
            case SDL_QUIT:  printf("exiting!\n");   return EXIT;
            default:        return NONE;
        }
    }
}