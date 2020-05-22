#include "mandel.h"

#define MANDEL_TEXT_BUF_SIZE 128

SDL_Texture	*text_texture_new(State *state, const char *fmt, ...)
{
	SDL_Texture	*texture;
	SDL_Surface	*surface;
	SDL_Color	color;
	char		buf[MANDEL_TEXT_BUF_SIZE];
	va_list		ap;

	va_start(ap, fmt);
	vsnprintf(buf, MANDEL_TEXT_BUF_SIZE, fmt, ap);
	va_end(ap);
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	TTF_CALL(surface = TTF_RenderText_Solid(state->font, buf, color));
	SDL_CALL(texture = SDL_CreateTextureFromSurface(state->renderer, surface));
	SDL_FreeSurface(surface);
	return texture;
}

void		text_render(State *state, SDL_Texture *texture, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_CALL(SDL_RenderCopy(state->renderer, texture, NULL, &dst));
}
