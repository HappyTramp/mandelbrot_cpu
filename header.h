#ifndef HEADER_H
# define HEADER_H

# include <stdbool.h>
# include <complex.h>
# include <SDL2/SDL.h>

# define REAL_LO -2.0
# define REAL_HI 2.0
# define IMAG_LO -2.0
# define IMAG_HI 2.0

# define MAX_ITERATION 30
# define _INFINITY 4

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running;
    int window_w;
    int window_h;
    double real_lo;
    double real_hi;
    double imag_lo;
    double imag_hi;
} GState;

// mandelbrot.c
int mandelbrot_in_set(double _Complex c);
void mandelbrot_print(void);

// graphics.c
GState *graphics_init(void);
void graphics_quit(GState *state);
void graphics_run(GState *state);

// helper.c
double map_range(double x, double src_lo, double src_hi, double dest_lo, double dest_hi);

#endif
