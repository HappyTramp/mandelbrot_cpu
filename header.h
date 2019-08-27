#ifndef HEADER_H
# define HEADER_H

# include <stdbool.h>
# include <complex.h>
# include <SDL2/SDL.h>

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running;
} GState;

typedef struct
{
    int window_width;
    int window_height;
} GConf;

// mandelbrot.c
double mandelbrot_in_set(double _Complex c);
void mandelbrot_print(void);

// graphics.c
GState *graphics_init(GConf *conf);
void graphics_quit(GState *state);
void graphics_run(GState *state);

#endif
