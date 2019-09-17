#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#define CHAR_SIZE sizeof(char)
#define DEFAULT_WINDOW_W 200
#define DEFAULT_WINDOW_H 200
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
                config.window_w = atoi(optarg);
                config.window_h = atoi(strstr(optarg, ",") + CHAR_SIZE);
                break;
            case 'r':
                config.real_range = atof(optarg);
                config.imag_range = atof(strstr(optarg, ",") + CHAR_SIZE);
                break;
            case 'c':
                config.center_x = atof(optarg);
                config.center_y = atof(strstr(optarg, ",") + CHAR_SIZE);
                break;
            case '?':
            default:
                fprintf(stderr, "Usage %s [pwh]", argv[0]);
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
