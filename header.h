#ifndef HEADER_H
# define HEADER_H

# include <stdbool.h>
# include <complex.h>
# include <SDL2/SDL.h>

# define WINDOW_W 500
# define WINDOW_H 500

# define LO -1.5
# define HI 1.5
# define AXIS_DIV 46.0
# define AXIS_STEP ((HI - LO) / AXIS_DIV)

# define MAX_ITERATION 50
# define _INFINITY 15


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

// helper.c
double map_range(double x, double src_lo, double src_hi, double dest_lo, double dest_hi);

#endif
