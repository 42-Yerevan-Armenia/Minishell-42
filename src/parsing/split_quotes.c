#include "../../includes/minishell.h"

//  "<<hd'" kddd|" dj $'* ><kkk -ld sdf"  rt' pwd|"$ho'|M

int	split_quotes(t_parse *parser)
{
	int i;
	int	l_arr;
	char c;
	char	*tmp;
	tmp = parser->rd_ln;
	int	j;
	int k;
	int t;

	k = 0;
	l_arr = 2;
	i = 0;
	parser->spl_qutoes = malloc(sizeof(char *) * (l_arr + 1));
	if (!parser->spl_qutoes && !ft_perror("minishell"))
		exit (1);
	fill_null(&parser->spl_qutoes, l_arr + 1);
	parser->spl_qutoes[l_arr] = NULL;
	while (tmp[i])
	{
		t = i;
		while (tmp[i] && (tmp[i] !=  '\'' && tmp[i] != '"'))
			i++;
		if (t != i)
		{
			if (l_arr == k)
				parser->spl_qutoes = resize_arr(parser->spl_qutoes, &l_arr);
			parser->spl_qutoes[k++] = ft_substr(tmp, t, i - t);
		}
		if (tmp[i] && (tmp[i] == '\'' || tmp[i] == '"'))
		{
			j = i;
			c = tmp[i++];
			while (tmp[i] && (tmp[i] != c && tmp[i] != c))
				i++;
			if (tmp[i] != c && printf("syntax error invalid quotes\n"))
				return (1);
			if (l_arr == k)
				parser->spl_qutoes = resize_arr(parser->spl_qutoes, &l_arr);
			parser->spl_qutoes[k++] = ft_substr(tmp, j, i - j + 1);
		}
		if (tmp[i])
			i++;
	}
	return (0);
}