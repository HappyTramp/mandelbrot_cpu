#ifndef HEADER_H
# define HEADER_H

# include <stdbool.h>
# include <SDL2/SDL.h>

# define MAX_ITERATION 200
# define ESCAPE_RADIUS 2
# define ESCAPE_RADIUS_SQUARED (ESCAPE_RADIUS * ESCAPE_RADIUS)

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
    bool moving;
} GState;

typedef struct
{
    int window_w;
    int window_h;
    double real_range;
    double imag_range;
    double center_x;
    double center_y;
} Config;

// mandelbrot.c
int mandelbrot_in_set(double a, double b);
void mandelbrot_print(void);
int *mandelbrot_array(Point center, double real_range, double imag_range,
                      double real_len, double imag_len);

// graphics.c
GState *graphics_init(Config *config);
void graphics_quit(GState *state);
void graphics_run(GState *state);
Color *create_palette(Color start, Color end);

// helper.c
double map_range(double x, double src_lo, double src_hi, double dest_lo, double dest_hi);

#endif
