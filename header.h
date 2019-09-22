#ifndef HEADER_H
# define HEADER_H

# include <stdbool.h>
# include <SDL2/SDL.h>

# define MAX_ITERATION 200
# define ESCAPE_RADIUS 10
# define ESCAPE_RADIUS_SQUARED (ESCAPE_RADIUS * ESCAPE_RADIUS)

# define PIXELS_CHANELS 3
# define PIXELS_DEPTH (PIXELS_CHANELS * 8)

typedef uint8_t Byte;
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
    bool changed;
    SDL_Texture *canvas;
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

typedef struct
{
    double real_lo;
    double real_hi;
    double imag_step;
    int width;
    double imag;
    Color *palette;
    uint8_t *row;
} ThreadArgs;

// mandelbrot.c
int mandelbrot_in_set(double a, double b);
void mandelbrot_print(void);
void *mandelbrot_pixels(double real_lo, double real_hi, double imag_lo,
                       double imag_hi, int width, int height, Color *palette);

// graphics.c
GState *graphics_init(Config *config);
void graphics_quit(GState *state);
void graphics_run(GState *state);

// helper.c
double map_range(double x, double src_lo, double src_hi, double dest_lo, double dest_hi);
Color helper_HSL_to_RGB(int hue, double saturation, double lightness);
double double_rand(void);

#endif
