#include "header.h"

int main(void)
{
    /* mandelbrot_print(); */
    GState *gstate = graphics_init();
    graphics_run(gstate);
    graphics_quit(gstate);
    return 0;
}
