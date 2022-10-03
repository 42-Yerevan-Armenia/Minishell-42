#include "../../includes/minishell.h"

//  "<<hd'" kddd" dj $'* ><kkk -ld sdf"  rt' pwd"$ho'M

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
	// parser->spl_qutoes = malloc(1000);
	if (!parser->spl_qutoes && printf("Can't allocate memory."))
		exit (1);
	parser->spl_qutoes[l_arr] = NULL;
	// printf("barev\n");
	// write(1, "1\n",2);
	while (tmp[i])
	{
		t = i;
		while (tmp[i] && (tmp[i] !=  '\'' && tmp[i] != '"'))
			i++;
		if (t != i)
		{
			if (l_arr == k)
				parser->spl_qutoes = resize_arr(parser->spl_qutoes, &l_arr);
			parser->spl_qutoes[k] = ft_substr(tmp, t, i - t);
			parser->spl_qutoes[k] = ft_strtrim(parser->spl_qutoes[k], " ");
			k++;
		}
		if (tmp[i] && (tmp[i] == '\'' || tmp[i] == '"'))
		{
			j = i;
			c = tmp[i++];
			while (tmp[i] && (tmp[i] != c && tmp[i] != c))
				i++;
			// printf("hajox\n");
			// printf("%d\n", i);
			// printf("tmp[i] = %c\n", tmp[i]);
			if (tmp[i] != c && printf("syntax error invalid quotes\n"))
				return (1);
			if (l_arr == k)
				parser->spl_qutoes = resize_arr(parser->spl_qutoes, &l_arr);
			parser->spl_qutoes[k++] = ft_substr(tmp, j, i - j + 1);
		}
		i++;
	}
	parser->spl_qutoes[k] = NULL;
	return (0);
}