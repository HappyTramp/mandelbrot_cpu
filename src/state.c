#include "config.h"
#include "mandel.h"

#define MANDEL_FONT_PATH "font/00_starmap.ttf"
#define MANDEL_FONT_SIZE 12

bool	state_init(State *state)
{
    SDL_CALL(SDL_Init(SDL_INIT_VIDEO));
	TTF_CALL(TTF_Init());
    SDL_CALL(state->window = SDL_CreateWindow(
		MANDEL_WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		MANDEL_WINDOW_WIDTH,
		MANDEL_WINDOW_HEIGHT,
		SDL_WINDOW_RESIZABLE
	));
    SDL_CALL(state->renderer = SDL_CreateRenderer(state->window, -1, 0));
	SDL_CALL(state->texture = SDL_CreateTexture(
		state->renderer,
		SDL_PIXELFORMAT_RGB888,
		SDL_TEXTUREACCESS_STREAMING,
		MANDEL_WINDOW_WIDTH,
		MANDEL_WINDOW_HEIGHT
	));
	TTF_CALL(state->font = TTF_OpenFont(MANDEL_FONT_PATH, MANDEL_FONT_SIZE));
	state->iterations = MANDEL_ITERATIONS;
	state->texture_iterations = text_texture_new(state, "iterations: %d", state->iterations);
	state->texture_time = text_texture_new(state, "time: 0ms");
	state->texture_center = text_texture_new(state, "center: 0i + 0");
	state->palette = color_palette_new(NULL, MANDEL_ITERATIONS);
	if (state->palette == NULL)
		return false;
	state->real_start = -2.0;
	state->real_end = 2.0;
	state->imag_start = -2.0;
	state->imag_end = 2.0;
    state->running = true;
	state->info = false;
    return true;
}

void	state_run(State *state)
{
    while (state->running)
    {
        event_handle(state);

		int		_;
		void	*pixels;
		int		width;
		int		height;

		SDL_CALL(SDL_LockTexture(state->texture, NULL, &pixels, &_));
		SDL_CALL(SDL_QueryTexture(state->texture, NULL, NULL, &width, &height));

		uint32_t render_start_time = SDL_GetTicks();
		mandelbrot_avx(state, pixels, width, height);
		uint32_t render_end_time = SDL_GetTicks();

		SDL_UnlockTexture(state->texture);
		SDL_CALL(SDL_RenderCopy(state->renderer, state->texture, NULL, NULL));
		if (state->info)
		{
			TEXT_TEXTURE_UPDATE(state, state->texture_time, "time: %u", render_end_time - render_start_time);
			text_render(state, state->texture_center,     10, 10, 200, 12);
			text_render(state, state->texture_iterations, 10, 30, 90, 12);
			text_render(state, state->texture_time,       10, 50, 45, 12);
		}

		SDL_RenderPresent(state->renderer);
		SDL_Delay(3);
    }
}

void	state_quit(State *state)
{
    free(state->palette);
	TTF_CloseFont(state->font);
	SDL_DestroyTexture(state->texture_iterations);
	SDL_DestroyTexture(state->texture_center);
	SDL_DestroyTexture(state->texture_time);
	SDL_DestroyTexture(state->texture);
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
	TTF_Quit();
	SDL_Quit();
}
