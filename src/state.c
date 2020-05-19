#include "config.h"
#include "mandel.h"

bool	state_init(State *state)
{
    SDL_CALL(SDL_Init(SDL_INIT_VIDEO));
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
	state->palette = color_palette_new(NULL, MANDEL_ITERATIONS);
	if (state->palette == NULL)
		return false;
	state->iterations = MANDEL_ITERATIONS;
	state->real_start = -2.0;
	state->real_end = 2.0;
	state->imag_start = -2.0;
	state->imag_end = 2.0;
    state->running = true;
    return true;
}

void	state_run(State *state)
{
    while (state->running)
    {
        event_handle(state);

		double	real_step;
		double	imag_step;
		double	real;
		double	imag;
		void	*pixels;
		int		pitch;
		int		width;
		int		height;

		SDL_CALL(SDL_LockTexture(state->texture, NULL, &pixels, &pitch));
		SDL_CALL(SDL_QueryTexture(state->texture, NULL, NULL, &width, &height));

		real_step = (state->real_end - state->real_start) / width;
		imag_step = (state->imag_end - state->imag_start) / height;
		imag = state->imag_start;

		uint32_t render_start_time = SDL_GetTicks();

		for (int i = 0; i < height; i++)
		{
			real = state->real_start;
			for (int j = 0; j < width; j++)
			{
				int n = mandelbrot(real, imag, state->iterations);
				Color c = state->palette[n];
				((Color*)pixels)[i * width + j] = c;
				real += real_step;
			}
			imag += imag_step;
		}

		uint32_t render_end_time = SDL_GetTicks();

		printf("%ums\r", (render_end_time - render_start_time));
		fflush(stdout);

		SDL_UnlockTexture(state->texture);
		SDL_CALL(SDL_RenderCopy(state->renderer, state->texture, NULL, NULL));
		SDL_RenderPresent(state->renderer);
		SDL_Delay(3);
    }
}

void	state_quit(State *state)
{
    free(state->palette);
	SDL_DestroyTexture(state->texture);
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
	SDL_Quit();
}
