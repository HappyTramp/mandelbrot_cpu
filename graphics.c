#include <stdbool.h>
#include <complex.h>
#include <SDL2/SDL.h>
#include "header.h"

#define WINDOW_TITLE "Mandelbrot"
#define WINDOW_X 20
#define WINDOW_Y 20
#define WINDOW_W 300
#define WINDOW_H 300
#define REFRESH_RATE 1
#define MOVE_RATIO 10
#define ZOOM_RATIO 1.1
#define REAL_LO(state) (state->center.x - state->real_range / 2)
#define REAL_HI(state) (state->center.x + state->real_range / 2)
#define IMAG_LO(state) (state->center.y - state->imag_range / 2)
#define IMAG_HI(state) (state->center.y + state->imag_range / 2)

#define RED_MASK 0xFF0000
#define GREEN_MASK 0x00FF00
#define BLUE_MASK 0x0000FF
#define RED(c) ((c & RED_MASK) >> (8 * 2))
#define GREEN(c) ((c & GREEN_MASK) >> 8)
#define BLUE(c) (c & BLUE_MASK)
#define MERGE_RGB(r, g, b) ((r) << (8 * 2) | (g) << 8 | (b))
#define PALETTE_START 0x000022
#define PALETTE_END 0xd62f2f
#define SET_DRAW_COLOR_RGB(renderer, c) ( \
        SDL_SetRenderDrawColor(renderer, RED(c), GREEN(c), BLUE(c), SDL_ALPHA_OPAQUE))
#define IN_SET_COLOR 0x000000

static void update(GState *state);
static void event_handler(GState *state);
static Color *create_palette(Color start, Color end);
static void destroy_state(GState *state);
static void error_exit_state(GState *state, const char *msg);
static void error_exit(const char *msg);

GState *graphics_init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        error_exit("unable to init SDL");
    GState *state = (GState*)malloc(sizeof(GState));
    if (state == NULL)
        error_exit("state allocation failed");
    state->window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_X, WINDOW_Y,
                                     WINDOW_W, WINDOW_H, 0);
    if (state->window == NULL)
        error_exit_state(state, "unable to create window");
    state->renderer = SDL_CreateRenderer(state->window, -1, 0);
    if (state->renderer == NULL)
        error_exit_state(state, "unable to create renderer");
    if ((state->palette = create_palette(PALETTE_START, PALETTE_END)) == NULL)
        error_exit_state(state, "unable to create color palette");
    state->running = true;
    state->window_w = WINDOW_W;
    state->window_h = WINDOW_H;
    state->real_range = REAL_RANGE;
    state->imag_range = IMAG_RANGE;
    state->center.x = CENTER_X;
    state->center.y = CENTER_Y;
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
    double a, b;
    SET_DRAW_COLOR_RGB(state->renderer, IN_SET_COLOR);
    SDL_RenderClear(state->renderer);
    for (int x = 0; x < state->window_w; x++)
    {
        for (int y = 0; y < state->window_h; y++)
        {
            a = map_range((double)x, 0, state->window_w, REAL_LO(state), REAL_HI(state));
            b = map_range((double)y, 0, state->window_h, IMAG_LO(state), IMAG_HI(state));
            double complex mapped_z = a + b * I;
            int steps = mandelbrot_in_set(mapped_z);
            if (steps == -1)
                continue;
            SET_DRAW_COLOR_RGB(state->renderer, state->palette[steps]);
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
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                    case SDLK_UP:
                    case SDLK_k:
                        state->center.y -= state->imag_range / MOVE_RATIO;
                        break;
                    case SDLK_DOWN:
                    case SDLK_j:
                        state->center.y += state->imag_range / MOVE_RATIO;
                        break;
                    case SDLK_LEFT:
                    case SDLK_h:
                        state->center.x -= state->real_range / MOVE_RATIO;
                        break;
                    case SDLK_RIGHT:
                    case SDLK_l:
                        state->center.x += state->real_range / MOVE_RATIO;
                        break;
                    case SDLK_PLUS:
                    case SDLK_p:
                        state->real_range /= ZOOM_RATIO;
                        state->imag_range /= ZOOM_RATIO;
                        break;
                    case SDLK_MINUS:
                    case SDLK_m:
                        state->real_range *= ZOOM_RATIO;
                        state->imag_range *= ZOOM_RATIO;
                        break;
                    case SDLK_q:
                        state->running = false;
                }
        }
    }
}

static Color *create_palette(Color start, Color end)
{
    Color red_step = abs(RED(end) - RED(start)) / MAX_ITERATION;
    Color green_step = abs(GREEN(end) - GREEN(start)) / MAX_ITERATION;
    Color blue_step = abs(BLUE(end) - BLUE(start)) / MAX_ITERATION;

    Color *palette = (Color*)malloc(sizeof(Color) * MAX_ITERATION);
    if (palette == NULL)
        return NULL;
    for (int i = 0; i < MAX_ITERATION; i++)
        palette[i] = MERGE_RGB(i * red_step + RED(start),
                               i * green_step + GREEN(start),
                               i * blue_step + BLUE(start));
    return palette;
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
