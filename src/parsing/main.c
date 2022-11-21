/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:29:53 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/20 16:47:00 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 1;

static int	ft_readline_main(t_parse *parser, t_data *data)
{
	set_term_attr(TC_OFF);
	// if (g_sig == 100)
	// {
	// 	rl_on_new_line();
	// 	rl_replace_line("", 0);
	// 	g_sig = 0;
	// }
	// printf("hajox1");
	parser->rd_ln = readline("🔻minishell> ");
	// printf("hajox");
	if (g_sig == 0 && ++g_sig && !free_arr(&parser->rd_ln))
	{
		set_env(data, new_env("?=", "1", FORME));
		return (1);
	}
	set_term_attr(TC_ON);
	if (!parser->rd_ln)
		exit(1);
	return (0);
}

static void	start(t_parse *parser, t_data *data)
{
	while (!free_arr(&parser->rd_ln))
	{
		if (ft_readline_main(parser, data) == 1)
			continue ;
		if (parser->rd_ln[0])
		{
			add_history(parser->rd_ln);
			if (parsing(parser) == START_RD_LN
				&& !ft_get_status_in_env(data, parser))
				continue ;
			if (data->cmd_line->head && data->cmd_line->head->cmd)
			{
				execute(data);
			}
		}
		ft_get_status_in_env(data, parser);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_parse	parser;
	t_data	data;

	(void)av;
	if (ac == 1)
	{
		init(&parser, &data, envp);
		data.builtins = ft_bultins();
		hook_signals();
		start(&parser, &data);
	}
	return (0);
}
