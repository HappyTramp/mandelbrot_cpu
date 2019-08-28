#include <stdbool.h>
#include <complex.h>
#include <SDL2/SDL.h>
#include "header.h"

#define WINDOW_TITLE "Mandelbrot"
#define WINDOW_X 20
#define WINDOW_Y 20
#define WINDOW_W 300
#define WINDOW_H 300
#define REFRESH_RATE 3
#define MOVE_SIZE 0.1
#define ZOOM_SIZE 0.1

#define BRIGHTNESS_LO 0
#define BRIGHTNESS_HI 10

static void update(GState *state);
static void event_handler(GState *state);
static void destroy_state(GState *state);
static void error_exit_state(GState *state, const char *msg);
static void error_exit(const char *msg);

GState *graphics_init(void)
{
    GState *state = (GState*)malloc(sizeof(GState));
    if (state == NULL)
        return NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        error_exit("unable to init SDL");
    state->window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_X, WINDOW_Y,
                                     WINDOW_W, WINDOW_H, 0);
    if (state->window == NULL)
        error_exit("unable to create window");
    state->renderer = SDL_CreateRenderer(state->window, -1, 0);
    if (state->renderer == NULL)
        error_exit_state(state, "unable to create renderer");
    state->running = true;
    state->window_w = WINDOW_W;
    state->window_h = WINDOW_H;
    state->real_lo = REAL_LO;
    state->real_hi = REAL_HI;
    state->imag_lo = IMAG_LO;
    state->imag_hi = IMAG_HI;
    return state;
}

void graphics_quit(GState *state)
{
    destroy_state(state);
    SDL_Quit();
}

void graphics_run(GState *state)
{
    while (state->running)
    {
        event_handler(state);
        update(state);
        SDL_Delay(REFRESH_RATE);
    }
}

static void update(GState *state)
{
    double a, b, brightness;
    SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(state->renderer);
    for (int x = 0; x < state->window_w; x++)
    {
        for (int y = 0; y < state->window_h; y++)
        {
            a = map_range((double)x, 0, state->window_w, state->real_lo, state->real_hi);
            b = map_range((double)y, 0, state->window_h, state->imag_lo, state->imag_hi);
            double complex mapped_z = a + b * I;
            int steps = mandelbrot_in_set(mapped_z);
            if (steps == -1)
                continue;
            brightness = map_range(steps, state->real_lo, state->real_hi,
                                   BRIGHTNESS_LO, BRIGHTNESS_HI);
            SDL_SetRenderDrawColor(state->renderer, brightness, brightness,
                                   brightness, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(state->renderer, x, y);
        }
    }
    SDL_RenderPresent(state->renderer);
}

static void event_handler(GState *state)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
            case SDL_QUIT:
                state->running = false;
                break;
            case SDL_KEYUP:
                switch (e.key.keysym.sym)
                {
                    case SDLK_UP:
                        state->imag_lo -= MOVE_SIZE;
                        state->imag_hi -= MOVE_SIZE;
                        break;
                    case SDLK_DOWN:
                        state->imag_lo += MOVE_SIZE;
                        state->imag_hi += MOVE_SIZE;
                        break;
                    case SDLK_LEFT:
                        state->real_lo -= MOVE_SIZE;
                        state->real_hi -= MOVE_SIZE;
                        break;
                    case SDLK_RIGHT:
                        state->real_lo += MOVE_SIZE;
                        state->real_hi += MOVE_SIZE;
                        break;
                    case SDLK_p:
                        state->real_lo += ZOOM_SIZE;
                        state->real_hi -= ZOOM_SIZE;
                        state->imag_lo += ZOOM_SIZE;
                        state->imag_hi -= ZOOM_SIZE;
                        break;
                    case SDLK_m:
                        state->real_lo -= ZOOM_SIZE;
                        state->real_hi += ZOOM_SIZE;
                        state->imag_lo -= ZOOM_SIZE;
                        state->imag_hi += ZOOM_SIZE;
                        break;
                }
        }
    }
}

static void destroy_state(GState *state)
{
    if (state == NULL)
        return;
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    free(state);
}

static void error_exit_state(GState *state, const char *msg)
{
    destroy_state(state);
    error_exit(msg);
}

static void error_exit(const char *msg)
{
    SDL_Log("ERROR: %s: %s", SDL_GetError(), msg);
    SDL_Quit();
    exit(EXIT_FAILURE);
}
