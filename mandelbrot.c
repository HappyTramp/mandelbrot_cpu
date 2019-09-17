#include <stdio.h>
#include <math.h>
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

int mandelbrot_in_set(double ca, double cb)
{
    double zr = ca;
    double zi = cb;
    double zr_square;
    double zi_square;
    for (int n = 0; n < MAX_ITERATION; n++)
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
    return -1;
}

ColorHexcode mandelbrot_in_set_color(Color *spectrum, double a, double b)
{
    int steps = mandelbrot_in_set(a, b);
    int brightness = (255 / MAX_ITERATION) * steps;
    Color color;
    color.rgb.r = brightness;
    color.rgb.g = brightness;
    color.rgb.b = brightness;
    return color.hexcode;
}

uint8_t *mandelbrot_create_bits(int width, int height)
{
    uint8_t *bits = (uint8_t*)malloc(3 * width * height);
    if (bits == NULL)
        return NULL;
    return bits;
}

void mandelbrot_set_bits(uint8_t *bits, Color *spectrum, Point center, double real_range,
                         double imag_range, int width, int height)
{
    double i = center.y - imag_range / 2;
    double r = center.x - real_range / 2;

    for (int array_i = 0; array_i < height;  array_i++)
    {
        for (int array_j = 0; array_j < width; array_j++)
        {
            bits[array_i * (int)height + array_j] = mandelbrot_in_set_color(spectrum, r, i);
            r += real_range / width;
        }
        i += imag_range / height;
    }
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
