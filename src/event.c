#include "mandel.h"

void event_handle(State *state)
{
    SDL_Event	e;

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

                        break;
                    case SDLK_DOWN:
                    case SDLK_j:

                        break;
                    case SDLK_LEFT:
                    case SDLK_h:

                        break;
                    case SDLK_RIGHT:
                    case SDLK_l:

                        break;
                    case SDLK_PLUS:
                    case SDLK_p:

                        break;
                    case SDLK_MINUS:
                    case SDLK_m:

                        break;
                    case SDLK_q:
                        state->running = false;
                }
                break;
            case SDL_MOUSEWHEEL:
                if (e.wheel.y == -1)
					;
                else if (e.wheel.y == 1)
					;
                break;
            case SDL_MOUSEBUTTONDOWN:
				break;
        }
    }
}

