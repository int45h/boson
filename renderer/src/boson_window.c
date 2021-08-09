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
    if (w->w != NULL)
        SDL_DestroyWindow(w->w);
    if (w->r != NULL)
        SDL_DestroyRenderer(w->r);
    if (w->t != NULL)
        SDL_DestroyTexture(w->t);

    w->width = w->height = 0;
    w->ar = -1;
}

Window bCreateWindow(size_t w, size_t h, const char * title)
{
    Window disp;
    disp.w          = SDL_CreateWindow( title, 
                                        SDL_WINDOWPOS_CENTERED, 
                                        SDL_WINDOWPOS_CENTERED, 
                                        w, 
                                        h, 
                                        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    disp.r          = SDL_CreateRenderer(disp.w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    disp.t          = SDL_CreateTexture(disp.r, 
                                        SDL_PIXELFORMAT_RGBA8888,
                                        SDL_TEXTUREACCESS_STREAMING,
                                        w,
                                        h);
    disp.wContext   = SDL_GL_CreateContext(disp.w);
    disp.width      = w;
    disp.height     = h;
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

void bPushFrameBuffer(const uint32_t * fb, Window * w)
{
    SDL_UpdateTexture(w->t, NULL, (void*)fb, w->width*sizeof(uint32_t));
    SDL_RenderCopy(w->r, w->t, NULL, NULL);
}

void bRefreshWindow(Window * w)
{
    SDL_RenderPresent(w->r);
}

void bUpdateWindow(Window * w)
{
    SDL_GL_SwapWindow(w->w);
}

char bGetKeycode(Window * w)
{
    return w->e.key.keysym.sym;
}

void bResizeWindow(Window * win, size_t w, size_t h)
{
    SDL_SetWindowSize(win->w, w, h);
    win->ar = (float)w/(float)h;
    win->width  = w;
    win->height = h;
}

bEvents bPollEvent(Window * w)
{
    while(SDL_PollEvent(&w->e)){
        switch (w->e.type)
        {
            case SDL_QUIT:
            return B_EXIT;
            case SDL_WINDOWEVENT:   
                switch (w->e.window.event)
                {
                    case SDL_WINDOWEVENT_RESIZED:   
                    return B_WINDOW_RESIZE;
                }
            case SDL_KEYDOWN:
            return B_KEYDOWN;
            break;
        }
    }
}

void bQuit()
{
    SDL_Quit();
}