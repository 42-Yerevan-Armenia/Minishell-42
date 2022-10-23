#include "minishell.h"

char	*ft_strjoin_all(char **str)
{
	int i;
	char	*res;

	i = 0;
	res = malloc(1);
	res[0] = '`';
	while (str[i])
		res = ft_strjoin(res, str[i++]);
	res = ft_strjoin(res, "'");
	return (res);
}
