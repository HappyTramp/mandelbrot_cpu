#include <stdio.h>
#include <pthread.h>
#include "header.h"

#define PRINT_REAL_LO -2.0
#define PRINT_REAL_HI 2.0
#define PRINT_IMAG_LO -2.0
#define PRINT_IMAG_HI 2.0
#define AXIS_DIV 46.0
#define REAL_AXIS_STEP ((PRINT_REAL_HI - PRINT_REAL_LO) / AXIS_DIV)
#define IMAG_AXIS_STEP ((PRINT_IMAG_HI - PRINT_IMAG_LO) / AXIS_DIV)

#define IN_CHAR '*'
#define OUT_CHAR ' '

static void *pixel_row(void *args);

int mandelbrot_in_set(double ca, double cb)
{
    double zr = ca;
    double zi = cb;
    double zr_square;
    double zi_square;
    int n;
    for (n = 0; n < MAX_ITERATION; n++)
    {
        zi_square = zi * zi;
        zr_square = zr * zr;
        if (zr_square + zi_square > ESCAPE_RADIUS_SQUARED)
            return n;
            /* return n + 5 - clog(ESCAPE_RADIUS) / log(2); */
        zi = 2 * zr * zi;
        zr = zr_square - zi_square;
        zi += cb;
        zr += ca;
    }
    return n;
}

void *mandelbrot_pixels(double real_lo, double real_hi, double imag_lo,
                        double imag_hi, int width, int height, Color *palette)
{
    Byte *pixels = (Byte*)malloc(width * height * PIXELS_CHANELS);
    if (pixels == NULL)
        return NULL;
    pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t) * height);
    if (threads == NULL)
        return NULL;
    for (int y = 0; y < height; y++)
    {
        ThreadArgs *args = (ThreadArgs*)malloc(sizeof(ThreadArgs));
        if (args == NULL)
            return NULL;
        args->real_lo = real_lo;
        args->real_hi = real_hi;
        args->width = width;
        args->imag = map_range((double)y, 0, height, imag_lo, imag_hi);
        args->palette = palette;
        args->row = pixels + PIXELS_CHANELS * width * y;
        pthread_create(&threads[y], NULL, pixel_row, args);
    }
    for (int y = 0; y < height; y++)
        pthread_join(threads[y], NULL);
    free(threads);
    return (void*)pixels;
}

static void *pixel_row(void *void_args)
{
    ThreadArgs *args = (ThreadArgs*)void_args;
    for (int x = 0; x < args->width; x++)
    {
        double a = map_range((double)x, 0, args->width, args->real_lo, args->real_hi);
        Color color = args->palette[mandelbrot_in_set(a, args->imag)];
        args->row[x * PIXELS_CHANELS] = color.rgb.r;
        args->row[x * PIXELS_CHANELS + 1] = color.rgb.g;
        args->row[x * PIXELS_CHANELS + 2] = color.rgb.b;
    }
    free(args);
    return NULL;
}

void mandelbrot_print(void)
{
    for (double i = PRINT_IMAG_LO; i < PRINT_IMAG_HI; i += IMAG_AXIS_STEP)
    {
        for (double r = PRINT_REAL_LO; r < PRINT_REAL_HI; r += REAL_AXIS_STEP)
        {
            if (mandelbrot_in_set(r, i) == -1)
                putchar(IN_CHAR);
            else
                putchar(OUT_CHAR);
            putchar(' ');
        }
        putchar('\n');
    }
}
