#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <term.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

#define ERROR			-1
#define KEY_LEFT		4479771
#define KEY_RIGHT		4414235
#define KEY_UP			4283163
#define KEY_DOWN		4348699
#define KEY_BACKSPACE	127
#define CURPOS			"\033[6n"

const char				*g_cm;
const char				*g_ce;
const char				*g_dc;

bool	init_term(struct termios *t)
{
	if (tcgetattr(STDIN_FILENO, t) == ERROR)
		return (false);
	t->c_lflag &= ~(ICANON | ECHO);
	t->c_cc[VMIN] = 1;
	t->c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, t) == ERROR)
		return (false);
	return (true);
}

bool	init_query(void)
{
	if (tgetent(NULL, "xterm") == ERROR)
		return (false);
	g_cm = tgetstr("cm", NULL);
	g_ce = tgetstr("ce", NULL);
	g_dc = tgetstr("dc", NULL);
	if (!g_cm || !g_ce)
		return (false);
	return (true);
}

int		putchar(int c)
{
	if (write(STDOUT_FILENO, &c, 1) == ERROR)
		return (0);
	return (1);
}

bool	get_position(int *col, int *row)
{
	int					i;
	int					ret;
	char				buf[1024];

	int testfile = open("testfile", O_RDWR | O_CREAT);

	if (write(STDOUT_FILENO, CURPOS, strlen(CURPOS)) == ERROR)
		return (false);
	ret = read(STDIN_FILENO, buf, 1024);
	if (ret == ERROR)
		return (false);
	buf[ret] = '\0';

	write(testfile, buf, strlen(buf));

	i = 0;
	while (!isdigit(buf[i]))
		++i;
	*row = atoi(&buf[i]) - 1;
	while (isdigit(buf[i]))
		++i;
	while (!isdigit(buf[i]))
		++i;
	*col = atoi(&buf[i]) - 1;
	return (true);
}

bool	cur_left(int *col, int *row)
{
	if (*col)
	{
		--(*col);
		if (tputs(tgoto(g_cm, *col, *row), 1, putchar) == ERROR)
			return (false);
	}
	return (true);
}

bool	cur_right(int *col, int *row)
{
	++(*col);
	if (tputs(tgoto(g_cm, *col, *row), 1, putchar) == ERROR)
		return (false);
	return (true);
}

bool	cur_up(int *col, int *row)
{
	if (*row)
	{
		--(*row);
		if (tputs(tgoto(g_cm, *col, *row), 1, putchar) == ERROR)
			return (false);
	}
	return (true);
}

bool	cur_down(int *col, int *row)
{
	++(*row);
	if (tputs(tgoto(g_cm, *col, *row), 1, putchar) == ERROR)
		return (false);
	return (true);
}

bool	cur_backspace(int *col, int *row)
{
	if (*col)
	{
		--(*col);
		if (tputs(tgoto(g_cm, *col, *row), 1, putchar) == ERROR)
			return (false);
	}
	if (tputs(g_dc, 1, putchar) == ERROR)
		return (false);
	return (true);
}

bool	key_handle(int ch, int *col, int *row)
{
	if (ch == KEY_LEFT)
	{
		if (!cur_left(col, row))
			return (false);
	}
	else if (ch == KEY_RIGHT)
	{
		if (!cur_right(col, row))
			return (false);
	}
	else if (ch == KEY_UP)
	{
		if (!cur_up(col, row))
			return (false);
	}
	else if (ch == KEY_DOWN)
	{
		if (!cur_down(col, row))
			return (false);
	}
	else if (ch == KEY_BACKSPACE)
	{
		if (!cur_backspace(col, row))
			return (false);
	}
	else
	{
		++(*col);
		if (!putchar(ch))
			return (false);
	}
	return (true);
}

bool	read_char(void)
{
	int					ch;
	int					ret;
	int					col;
	int					row;

	while (true)
	{
		if (!get_position(&col, &row))
			return (false);
		ret = read(STDIN_FILENO, &ch, sizeof(ch));
		if (ret == ERROR)
			return (false);
		if (!ret)
			return (true);
		if (!key_handle(ch, &col, &row))
			return (false);
		ch = 0;
	}
}

int		main(void)
{
	struct termios		t;

	if (!init_term(&t) || !init_query() || !read_char())
		return (1);
	return (0);
}
