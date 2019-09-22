#include <math.h>
#include "header.h"

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MIN3(x, y, z) (MIN(x, MIN(y, z)))

double map_range(double x, double src_lo, double src_hi, double dest_lo, double dest_hi)
{
    double src_len = src_hi - src_lo;
    double dest_len = dest_hi - dest_lo;
    return (x - src_lo) / src_len * dest_len + dest_lo;
}

Color helper_HSL_to_RGB(int hue, double saturation, double lightness)
{
    /* double chroma = (1 - fabs(2 * lightness - 1)) * saturation; */
    /* int hue_p = hue / 60; */
    /* double x = chroma * (1 - abs(hue_p % 2 - 1)); */
    Color color;

    /* if (hue == 0) */
    /* { */
    /*     color.hexcode = 0x000000; */
    /*     return color; */
    /* } */
    /*  */
    /* if (hue_p */

    double a = saturation * MIN(lightness, 1 - lightness);
    int kn0 = (0 + hue / 30) % 12;
    int kn8 = (8 + hue / 30) % 12;
    int kn4 = (4 + hue / 30) % 12;
    Byte f0 = lightness - a * MAX(MIN3(kn0 - 3, 9 - kn0, 1), -1);
    Byte f8 = lightness - a * MAX(MIN3(kn8 - 3, 9 - kn8, 1), -1);
    Byte f4 = lightness - a * MAX(MIN3(kn4 - 3, 9 - kn4, 1), -1);

    color.rgb.r = f0;
    color.rgb.g = f8;
    color.rgb.b = f4;

    return color;
}

double double_rand(void)
{
    return (double)rand() / RAND_MAX;
}
