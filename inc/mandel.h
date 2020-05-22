#ifndef MANDEL_H
# define MANDEL_H

# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <immintrin.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>

# define SDL_CALL(x) do {                    \
	SDL_ClearError();                        \
	x;                                       \
	error_check_sdl(#x, __FILE__, __LINE__); \
} while (0)

# define TTF_CALL SDL_CALL

enum
{
	KEY_UP = 0,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT,

	KEY_INC_ITERATIONS,
	KEY_DEC_ITERATIONS,

	KEY_ZOOM_IN,
	KEY_ZOOM_OUT,
};

typedef union
{
    uint32_t		data;
    struct
    {
        uint8_t 	b;
        uint8_t 	g;
        uint8_t 	r;
    };
}					Color;

typedef struct
{
	uint8_t 	h;
	uint8_t 	s;
	uint8_t 	l;
}					ColorHSL;

typedef struct
{
    double			x;
    double			y;
}					Point;

typedef struct
{
    SDL_Window		*window;
    SDL_Renderer	*renderer;
    bool			running;

	TTF_Font		*font;
	SDL_Texture		*texture_center;
	SDL_Texture		*texture_iterations;
	SDL_Texture		*texture_time;
	bool			info;

    Color			*palette;
	SDL_Texture		*texture;

	double			real_start;
	double			real_end;
	double			imag_start;
	double			imag_end;
	int				iterations;
}					State;

// mandelbrot.c
int					mandelbrot(double ca, double cb, int iterations);

// state.c
bool				state_init(State *state);
void				state_quit(State *state);
void				state_run(State *state);

// event.c
void				event_handle(State *state);

// error.c
void				error_check_sdl(const char *code, const char *filename, int line_num);

// color.c
Color				*color_palette_new(Color *palette, int iterations);

// text.c
# define TEXT_TEXTURE_UPDATE(state, texture, fmt, ...) do {  \
	if (state->info) {                                       \
		SDL_DestroyTexture(texture);                         \
		texture = text_texture_new(state, fmt, __VA_ARGS__); \
	}                                                        \
} while(0)

SDL_Texture			*text_texture_new(State *state, const char *fmt, ...);
void				text_render(State *state, SDL_Texture *texture, int x, int y, int w, int h);

#endif
