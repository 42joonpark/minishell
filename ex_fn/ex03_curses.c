#include <curses.h>
#include <term.h>
#include <termcap.h>
#include <unistd.h>
#include <stdlib.h>

int	putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

int	main(void)
{
	char	*env;
	char	*cm;
	char	*ce;

	env = getenv("TERM");
	if (env == NULL)
		env = "xterm";
	tgetent(NULL, env);			// xterm 설정 사용
	cm = tgetstr("cm", NULL);	// cursor motion
	tputs(tgoto(cm, 12, 5), 1, putchar_tc);
	// ce = tgetstr("ce", NULL);	// clear line from cursor
	// tputs(ce, 1, putchar_tc);
	while (1);
	return (0);
}
