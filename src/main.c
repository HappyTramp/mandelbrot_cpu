#include "mandel.h"

int main(void)
{
    State state;

	if (!state_init(&state))
		return (1);
    state_run(&state);
	/* printf("yo\n"); */
    state_quit(&state);
    return EXIT_SUCCESS;
}
