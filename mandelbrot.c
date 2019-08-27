#include <stdio.h>
#include <math.h>
#include <complex.h>

#define LO -1.7
#define HI 1.7
#define AXIS_DIV 46.0
#define AXIS_STEP ((HI - LO) / AXIS_DIV)

#define MAX_ITERATION 1000
#define _INFINITY 1000

#define IN_CHAR '*'
#define OUT_CHAR ' '

/*
#define SQUARE(x) (pow((x), 2))
#define SQUARE_CML(z) (SQUARE(creal(z)) - SQUARE(cimag(z)) + 2 * creal(z) * cimag(z) * I)

double magnitude(double complex z)
{
    return sqrt(SQUARE(creal(z)) + SQUARE(cimag(z)));
}
*/

double mandelbrot_in_set(double complex c)
{
    int i;
    double complex z = 0;
    for (i = 0; i < MAX_ITERATION; i++)
    {
        z = cpow(z, 2) + c;
        if (cabs(z) > _INFINITY)
            return 0;
    }
    return 1;
}

void mandelbrot_print(void)
{
    for (double i = LO; i < HI; i += AXIS_STEP)
    {
        for (double r = LO; r < HI; r += AXIS_STEP)
        {
            if (mandelbrot_in_set(r + i * I))
                putchar(IN_CHAR);
            else
                putchar(OUT_CHAR);
            putchar(' ');
        }
        putchar('\n');
    }
}

