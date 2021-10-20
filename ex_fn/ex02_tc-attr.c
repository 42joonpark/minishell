#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_termios
{
	struct termios	org_termios;
	struct termios	new_termios;
}	t_termios;

// org_termios에 초기 터미널 세팅 저장
void	save_input_mode(t_termios *term)
{
	tcgetattr(STDIN_FILENO, &term->org_termios);	// STDIN으로부터 터미널 속성을 받아온다
}

// new_termios에 원하는 터미널 속성 설정
void	set_input_mode(t_termios *term)
{
	tcgetattr(STDIN_FILENO, &term->new_termios);	// STDIN으로부터 터미널 속성을 받아온다
	term->new_termios.c_lflag &= ~(ICANON | ECHO);	// non-canonical input 설정, 입력 시 터미널에 보이지 않게
	term->new_termios.c_cc[VMIN] = 1;		// 1 바이트씩 처리
	term->new_termios.c_cc[VTIME] = 0;		// 버퍼 비우는 시간
	tcsetattr(STDIN_FILENO, TCSANOW, &term->new_termios);	// 변경된 속성의 터미널을 STDIN에 바로 적용
}

// 초기 터미널 세팅으로 다시 변경
void	reset_input_mode(t_termios *term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &term->org_termios);	// STDIN에 기존의 터미널 속성을 바로 적용
}


int	main(void)
{
	t_termios	term;
	int			c;
	int			idx;

	save_input_mode(&term);
	set_input_mode(&term);
	c = 0;
	idx = -1;
	while (read(0, &c, sizeof(c)) > 0)
	{
		// 문자열의 처음에 들어왔을 때에는 프로그램 종료, 아닌 경우에는 무시하도록 하였음.
		if (c == 4)	// ctrl + d
		{
			if (idx == -1)
				exit(0);
			else
				continue ;
		}
		else if (c == 127) // backspace
		{
			if (idx >= 0)
			{
				idx--;
				/** \b : 커서가 한 칸 뒤로(왼쪽 방향키와 같은 기능).
				 * 따라서 벡스페이스 기능을 구현하기위해 공백을 넣어주고,
				 * 다시 커서를 지워진 위치로 옮김 */
				write(0, "\b \b", 3);
			}
		}
		else if (c == '\n')	// new line
			break ;
		else
		{
			idx++;
			write(0, &c, sizeof(c));
		}
		c = 0; // flush buffer
	}
	reset_input_mode(&term);
	return (0);
}
