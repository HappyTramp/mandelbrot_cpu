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
		0));
    SDL_CALL(state->renderer = SDL_CreateRenderer(state->window, -1, 0));
    state->running = true;
    return state;
}

void	state_run(State *state)
{
    while (state->running)
    {
        event_handle(state);
    }
}

void	state_quit(State *state)
{
    /* free(state->palette); */
    /* SDL_FreeSurface(state->surface); */
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
	SDL_Quit();
}
