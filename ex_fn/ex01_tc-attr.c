#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	struct termios	s_termios;
	int 			c;

	/* 터미널 옵션 제어 */
	tcgetattr(STDIN_FILENO, &s_termios);	// STDIN으로부터 터미널 속성을 받아온다
	s_termios.c_lflag &= ~ICANON;	// non-canonical input 설정
	s_termios.c_lflag &= ~ECHO;		// 입력 시 터미널에 보이지 않게
	// s_termios.c_lflag &= ~ISIG;	// 특수문자 무시 (ctrl + c) 역시 무시!
	s_termios.c_cc[VMIN] = 1;		// 1 바이트씩 처리
	s_termios.c_cc[VTIME] = 0;		// 버퍼 비우는 시간
	tcsetattr(STDIN_FILENO, TCSANOW, &s_termios);	// 변경된 속성의 터미널을 STDIN에 바로 적용

	c = 0;
	while (read(0, &c, sizeof(c)) > 0)
	{
		printf("keycode: %d\n", c);
		c = 0; // flush buffer
	}
	return (0);
}
