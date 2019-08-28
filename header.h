#ifndef HEADER_H
# define HEADER_H

# include <stdbool.h>
# include <complex.h>
# include <SDL2/SDL.h>

# define CENTER_X 0.0
# define CENTER_Y 0.0
# define REAL_RANGE 4.0
# define IMAG_RANGE 4.0

# define MAX_ITERATION 50
# define ESCAPE_VALUE 2

typedef unsigned char Byte;
typedef int ColorHexcode;

typedef union
{
    ColorHexcode hexcode;
    struct
    {
        Byte b;
        Byte g;
        Byte r;
    } rgb;
} Color;

typedef struct
{
    double x;
    double y;
} Point;

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running;
    int window_w;
    int window_h;
    Point center;
    double real_range;
    double imag_range;
    Color *palette;
    Color in_set_color;
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
