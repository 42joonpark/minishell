#include "minishell.h"

void clear_screen(void)
{
	static const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";

	write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 10);
}
