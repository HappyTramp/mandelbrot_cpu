#include <getopt.h>
#include "header.h"

int main(int argc, char **argv)
{
    int opt;

    while ((opt = getopt(argc, argv, "c")) != -1)
    {
        switch (opt)
        {
            case 'c':
                mandelbrot_print();
                exit(EXIT_SUCCESS);
                break;
            default:
                fprintf(stderr, "Usage %s ...", argv[0]);
        }

    }
    GState *gstate = graphics_init();
    graphics_run(gstate);
    graphics_quit(gstate);
    return EXIT_SUCCESS;
}
