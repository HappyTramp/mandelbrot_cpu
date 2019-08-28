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

#define IN_SET_COLOR 0x000000
#define PALETTE_START 0x000022
#define PALETTE_END 0xd62f2f
#define SET_DRAW_COLOR(renderer, c) ( \
        SDL_SetRenderDrawColor(renderer, c.rgb.r, c.rgb.g, c.rgb.b, SDL_ALPHA_OPAQUE));

static void update(GState *state);
static void event_handler(GState *state);
static Color *create_palette(Color start, Color end);
static void destroy_state(GState *state);
static void error_exit_state(GState *state, const char *msg);
static void error_exit(const char *msg);

GState *graphics_init(void)
{
    Color start, end;

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
    start.hexcode = PALETTE_START;
    end.hexcode = PALETTE_END;
    state->palette = create_palette(start, end);
    if (state->palette == NULL)
        error_exit_state(state, "unable to create color palette");
    state->in_set_color.hexcode = IN_SET_COLOR;
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
    Color color;
    SET_DRAW_COLOR(state->renderer, state->in_set_color);
    SDL_RenderClear(state->renderer);
    for (int x = 0; x < state->window_w; x++)
    {
        for (int y = 0; y < state->window_h; y++)
        {
            a = map_range((double)x, 0, state->window_w, REAL_LO(state), REAL_HI(state));
            b = map_range((double)y, 0, state->window_h, IMAG_LO(state), IMAG_HI(state));
            int steps = mandelbrot_in_set(a + b * I);
            if (steps == -1)
                continue;
            color =  state->palette[steps];
            SET_DRAW_COLOR(state->renderer, color);
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
    int red_step = abs(end.rgb.r - start.rgb.r) / MAX_ITERATION;
    int green_step = abs(end.rgb.g - start.rgb.g) / MAX_ITERATION;
    int blue_step = abs(end.rgb.b - start.rgb.b) / MAX_ITERATION;

    Color *palette = (Color*)malloc(sizeof(Color) * MAX_ITERATION);
    if (palette == NULL)
        return NULL;
    for (int i = 0; i < MAX_ITERATION; i++)
    {
        palette[i].rgb.r = i * red_step + start.rgb.r;
        palette[i].rgb.g = i * green_step + start.rgb.g;
        palette[i].rgb.b = i * blue_step + start.rgb.b;
    }
    return palette;
}

static void destroy_state(GState *state)
{
    if (state == NULL)
        return;
    free(state->palette);
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
