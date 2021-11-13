#include "libft.h"

int	ft_strcat(char **str, char buffer[])
{
	int				idx_1;
	int				idx_2;
	char	*temp;
	char	*del;

	idx_1 = 0;
	idx_2 = 0;
	while ((*str)[idx_1])
		++idx_1;
	while (buffer[idx_2])
		++idx_2;
	if (!(temp = (char *)malloc(sizeof(char) *\
					(idx_1 + idx_2 + 1))))
		return (-1);
	idx_1 = -1;
	idx_2 = -1;
	while ((*str)[++idx_1])
		temp[idx_1] = (*str)[idx_1];
	while (buffer[++idx_2])
		temp[idx_1 + idx_2] = buffer[idx_2];
	temp[idx_1 + idx_2] = '\0';
	del = *str;
	*str = temp;
	free(del);
	return (0);
}