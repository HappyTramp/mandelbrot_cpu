#include <math.h>
#include "header.h"

double map_range(double x, double src_lo, double src_hi, double dest_lo, double dest_hi)
{
    double src_len = fabs(src_hi - src_lo);
    double dest_len = fabs(dest_hi - dest_lo);

    return (x - src_lo) / src_len * dest_len + dest_lo;
}
