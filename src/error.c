#include "mandel.h"

void	error_check_sdl(const char *code, const char *filename, int line_num)
{
	const char	*err;

	err = SDL_GetError();
	if (*err == '\0')
		return ;
	SDL_Log("[ERROR SDL] %s\n\t(%s) at %s:%d", err, code, filename, line_num);
	SDL_Quit();
	exit(EXIT_FAILURE);
}
