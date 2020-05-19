#include "mandel.h"

int mandelbrot(double ca, double cb, int iterations)
{
    double	zr = ca;
    double	zi = cb;
    double	zr_square;
    double	zi_square;
    int		n;

    for (n = 0; n < iterations; n++)
    {
        zi_square = zi * zi;
        zr_square = zr * zr;
        if (zr_square + zi_square > 4.0)
            return n;
        zi = 2.0 * zr * zi;
        zr = zr_square - zi_square;
        zi += cb;
        zr += ca;
    }
    return n;
}
