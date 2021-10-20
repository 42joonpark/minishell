#include <termcap.h>
#include <curses.h>
#include <term.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

#define BACKSPACE 127
#define LEFT_ARROW 4479771
#define RIGHT_ARROW 4414235

int	nbr_length(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

/** "\033[6n"이라는 문자열을 STDIN에 출력하고 다시 읽는데,
 *  이는 ANSI 이스케이프 문자로 현재 커서의 위치를 STDIN에 출력해준다. */
void	get_cursor_position(int *col, int *rows)
{
	int		a = 0;
	int		i = 1;
	char	buf[255];
	int		ret;
	int		temp;

	int testfile = open("testfile", O_RDWR | O_CREAT);

	// write(0, "\033[6n", 4);  // report cursor location
	write(0, "\033[6n", strlen("\033[6n"));  // report cursor location
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	write(testfile, buf, ft_strlen(buf));
	write(testfile, "\n", 1);
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (a == 0)
				*rows = atoi(&buf[i]) - 1;
			else
			{
				temp = atoi(&buf[i]);
				*col = temp - 1;
			}
			a++;
			i += nbr_length(temp) - 1;
		}
		i++;
	}
}

int		putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void	move_cursor_left(int *col, int *row, char *cm)
{
	if (*col == 0)
		return ;
	(*col)--;
	tputs(tgoto(cm, *col, *row), 1, putchar_tc);

}

void	move_cursor_right(int *col, int *row, char *cm)
{
	(*col)++;
	tputs(tgoto(cm, *col, *row), 1, putchar_tc);

}

void	delete_end(int *col, int *row, char *cm, char *ce)
{
	if (*col != 0)
		(*col)--;
	tputs(tgoto(cm, *col, *row), 1, putchar_tc);
	tputs(ce, 1, putchar_tc);
}

void	print_cursor_to_testfile(int testfile, int row, int col)
{
	char	*row_str = ft_itoa(row);
	char	*col_str = ft_itoa(col);
	write(testfile, row_str, ft_strlen(row_str));
	write(testfile, ", ", 2);
	write(testfile, col_str, ft_strlen(col_str));
	write(testfile, "\n", 1);
}

int		main(void)
{
	/* change term settings */
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);		// STDIN으로부터 터미널 속성을 받아온다
	term.c_lflag &= ~(ICANON | ECHO);	// non-canonical input 설정, 입력 시 터미널에 보이지 않게
	term.c_cc[VMIN] = 1;		// 1 바이트씩 처리
	term.c_cc[VTIME] = 0;		// 버퍼 비우는 시간
	tcsetattr(STDIN_FILENO, TCSANOW, &term);	// 변경된 속성의 터미널을 STDIN에 바로 적용

	/* init termcap */
	tgetent(NULL, "xterm");
	char *cm = tgetstr("cm", NULL); //cursor motion
	char *ce = tgetstr("ce", NULL); //clear line from cursor

	int c = 0;
	int row;
	int col;

	// int testfile = open("testfile", O_RDWR | O_CREAT);

	while (read(0, &c, sizeof(c)) > 0)
	{
		get_cursor_position(&col, &row);
		// print_cursor_to_testfile(testfile, row, col);
		if (c == LEFT_ARROW)
			move_cursor_left(&col, &row, cm);
		else if (c == RIGHT_ARROW)
			move_cursor_right(&col, &row, cm);
		else if (c == BACKSPACE)
			delete_end(&col, &row, cm, ce);
		else
		{
			col++;
			write(0, &c, 1);
		}
		c = 0; //flush buffer
	}
	return (0);
}
