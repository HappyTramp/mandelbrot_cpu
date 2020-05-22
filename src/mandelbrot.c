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

void mandelbrot_avx(State *state, Color *pixels, int width, int height)
{
	__m256d real_step = _mm256_set1_pd((state->real_end - state->real_end) / (double)width);
	__m256d imag_step = _mm256_set1_pd((state->imag_end - state->imag_end) / (double)height);

	__m256i	ones       = _mm256_set1_epi64x(1);
	__m256i iterations = _mm256_set1_epi64x(state->iterations);

	__m256d	twos  = _mm256_set1_pd(2.0);
	__m256d	fours = _mm256_set1_pd(4.0);

	__m256d	offset = _mm256_setr_pd(0.0, 1.0, 2.0, 3.0);

	__m256d ci = _mm256_set1_pd(0.0);
	for (int y = 0; y < height; y++)
	{
		__m256d cr = _mm256_set1_pd(0.0);
		for (int x = 0; x < width; x += 4)
		{
			__m256d	zr = cr;
			__m256d	zi = ci;
			__m256d	zr_square;
			__m256d	zi_square;
			__m256i	n;

			/* while { */

				zi_square = _mm256_mul_pd(zi, zi);
				zr_square = _mm256_mul_pd(zr, zr);

				__m256d dist = _mm256_add_pd(zi_square, zr_square);
				__m256d escaped = _mm256_cmp_pd(dist, fours, _CMP_LT_OQ);


				// zi = 2.0 * zi * zr
				zi = _mm256_mul_pd(zi, zr);
				zi = _mm256_mul_pd(zi, twos);

				zr = _mm256_sub_pd(zr_square, zi_square);
				zi = _mm256_add_pd(zi, ci);
				zr = _mm256_add_pd(zr, cr);

			/* } */


			cr = _mm256_add_pd(cr, real_step);
		}
		ci = _mm256_add_pd(ci, imag_step);
	}
}
