/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:46:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/10 21:27:05 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  "<<hd'" |   kd|   dd|" dj $'* ><kkk -ld sdf"  rt' pwd|"$ho'|M

// int	find_exe(t_parse *parser, t_data *data)
// {
	
// }

int	check_syntax(t_parse *parser)
{
	char	*tmp;
	int		i;

	tmp = parser->rd_ln;
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '|')
		{
			if (tmp[i + 1] == '|' || tmp[i + 1] == '\0')
				return (1);
			while (tmp[i])
			{
				
				i++;
			}
			
		}
		i++;
	}
	
}

int parsing(t_parse *parser)
{

	printf("%d\n", check_quote(parser));
	// split_quotes(parser);
	// int i = 0;

	// // while (parser->spl_qutoes[i])
	// // {
	// // 	printf("%s\n", parser->spl_qutoes[i++]);
	// // }
	// // printf("=-----------------\n");
	// split_pipe(parser);
	// i = 0;
	// // while (parser->spl_pipe[i])
	// // {
	// // 	printf("%s\n", parser->spl_pipe[i++]);
	// // }
	// // printf("=-----------------\n");
	// pipe_join(parser);
	// i = 0;
	// while (parser->join_pipe[i])
	// {
	// 	printf("%s\n", parser->join_pipe[i++]);
	// }
	
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
		
		
	}
}
