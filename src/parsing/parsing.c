/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:46:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/01 21:05:28 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//  "<<hd'" kddd" dj $'* ><kkk -ld sdf"  rt' pwd"$ho'M

int split_pipe(t_parse *parser)
{
	char	**tmp;
	int		t;
	int		i;
	int		j;
	int		k;

	tmp = parser->spl_qutoes;
	parser->spl_pipe = malloc(sizeof(char *) * 15);
	i = -1;
	j = -1;
	k = 0;
	while (tmp[++i])
	{
		t = ++j;
		while (tmp[i][j])
		{
			if (tmp[i][0] == '\'' || tmp[i][0] == '"')
			{
				parser->spl_pipe[k++] = ft_strdup(tmp[i]);
				break ;
			}
			while (tmp[i][j] != '|')
				j++;
			parser->spl_pipe[k++] = ft_substr(tmp[i], t, j - t + 1);
		}
	}
	parser->spl_pipe[k] = NULL;
	return (0);
}

int parsing(t_parse *parser)
{
	split_quotes(parser);
	// split_pipe(parser);
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
	}
}

