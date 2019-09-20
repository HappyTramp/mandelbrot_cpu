#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#define DEFAULT_WINDOW_W 300
#define DEFAULT_WINDOW_H 300
#define DEFAULT_CENTER_X 0.0
#define DEFAULT_CENTER_Y 0.0
#define DEFAULT_REAL_RANGE 4.0
#define DEFAULT_IMAG_RANGE 4.0

static void print_help(void);

int main(int argc, char **argv)
{
    int opt;
    Config config;
    /* Image *image = NULL; */

    config.window_w = DEFAULT_WINDOW_W;
    config.window_h = DEFAULT_WINDOW_H;
    config.center_x = DEFAULT_CENTER_X;
    config.center_y = DEFAULT_CENTER_Y;
    config.real_range = DEFAULT_REAL_RANGE;
    config.imag_range = DEFAULT_IMAG_RANGE;
    while ((opt = getopt(argc, argv, "hps:r:c:")) != -1)
    {
        switch (opt)
        {
            case 'p':
                mandelbrot_print();
                exit(EXIT_SUCCESS);
                break;
            /* case 'i': */
            /*     image = image_init(); */
            case 'h':
                print_help();
                exit(EXIT_SUCCESS);
                break;
            case 's':
                sscanf(optarg, "%d,%d", &config.window_w, &config.window_h);
                break;
            case 'r':
                sscanf(optarg, "%lf,%lf", &config.real_range, &config.imag_range);
                break;
            case 'c':
                sscanf(optarg, "%lf,%lf", &config.center_x, &config.center_y);
                break;
            case '?':
            default:
                fprintf(stderr, "Try: %s -h for more information", argv[0]);
                exit(EXIT_FAILURE);
        }

    }
    /* if (image != NULL) */
    /* { */
    /*  */
    /*     return EXIT_SUCCESS; */
    /* } */
    GState *gstate = graphics_init(&config);
    graphics_run(gstate);
    graphics_quit(gstate);
    return EXIT_SUCCESS;
}

static void print_help(void)
{
    printf("help");
}
