#include "mandel.h"

int mandelbrot(double ca, double cb)
{
    double zr = ca;
    double zi = cb;
    double zr_square;
    double zi_square;
    int n;
    for (n = 0; n < 20; n++)
    {
        zi_square = zi * zi;
        zr_square = zr * zr;
        if (zr_square + zi_square > 4)
            return n;
        zi = 2 * zr * zi;
        zr = zr_square - zi_square;
        zi += cb;
        zr += ca;
    }
    return n;
}
