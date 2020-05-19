#include "mandel.h"

/* static Color *create_palette(Color start, Color end) */
/* { */
    /* int red_step = abs(end.rgb.r - start.rgb.r) / MAX_ITERATION; */
    /* int green_step = abs(end.rgb.g - start.rgb.g) / MAX_ITERATION; */
    /* int blue_step = abs(end.rgb.b - start.rgb.b) / MAX_ITERATION; */
    /*  */
    /* Color *palette = (Color*)malloc(sizeof(Color) * (MAX_ITERATION + 1)); */
    /* if (palette == NULL) */
    /*     return NULL; */
    /* for (int i = 0; i < MAX_ITERATION; i++) */
    /* { */
    /*     #<{(| palette[i] = helper_HSL_to_RGB(i, 0.6, 1.0); |)}># */
    /*     #<{(| printf("%x\n", palette[i].hexcode); |)}># */
    /*     palette[i].rgb.r = i * red_step + start.rgb.r; */
    /*     palette[i].rgb.g = i * green_step + start.rgb.g; */
    /*     palette[i].rgb.b = i * blue_step + start.rgb.b; */
    /* } */
    /* palette[MAX_ITERATION].hexcode = 0x0; */
    /* return palette; */
/* } */
