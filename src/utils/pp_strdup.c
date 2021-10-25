#include "minishell.h"

char	*pp_strdup(const char *s1)
{
	char	*dst;

	dst = (char *)malloc((pp_strlen(s1) + 1) * sizeof(char));
	if (dst == NULL)
		return (0);
	pp_strlcpy(dst, s1, pp_strlen(s1) + 1);
	return (dst);
}
