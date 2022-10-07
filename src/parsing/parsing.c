/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:46:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/04 21:28:50 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  "<<hd'"| kddd|" dj $'* ><kkk -ld sdf"  rt' pwd|"$ho'|M

int split_pipe(t_parse *parser)
{
	char	**tmp;
	int		l_arr;
	int		t;
	int		i;
	int		j;
	int		k;

	tmp = parser->spl_qutoes;
	l_arr = 2;
	parser->spl_pipe = malloc(sizeof(char *) * (l_arr + 1));
	i = -1;
	j = 0;
	k = 0;
	while (tmp[++i])
	{
		while (tmp[i] && (tmp[i][0] == '\'' || tmp[i][0] == '"'))
			parser->spl_pipe[k++] = ft_strdup(tmp[i++]);
		while (tmp[i] && tmp[i][j])
		{
			t = j;
			while (tmp[i][j] && tmp[i][j] != '|')
				j++;
			if ( j != 0)
			{
				parser->spl_pipe[k++] = ft_substr(tmp[i], t, j - t);
				parser->spl_qutoes[k] = ft_strtrim(parser->spl_qutoes[k], " ");
				k++;
			}
			if (tmp[i][j] == '|')
			{
				parser->spl_pipe[k] = ft_strdup("|");
				parser->spl_qutoes[k] = ft_strtrim(parser->spl_qutoes[k], " ");
				k++;
			}
			
			// printf("spl_pipe[k++] = %s\n", parser->spl_pipe[k++]);
			j++;
		}
		j = 0;
	}
	parser->spl_pipe[k] = NULL;
	return (0);
}

int parsing(t_parse *parser)
{
	split_quotes(parser);
	split_pipe(parser);
	return (0);
}

int main(int ac, char **av)
{
	t_parse parser;

	if (ac == 1)
	{
		// while (1)
		// {
			parser.rd_ln = readline("minishell> ");
			parsing(&parser);
		// }
		int i = 0;

		while (parser.spl_qutoes[i])
		{
			printf("%s\n", parser.spl_qutoes[i++]);
		}
		printf("=-----------------\n");
		i = 0;
		while (parser.spl_pipe[i])
		{
			printf("%s\n", parser.spl_pipe[i++]);
		}
	}
}

