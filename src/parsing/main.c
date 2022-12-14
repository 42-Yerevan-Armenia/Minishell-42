/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:29:53 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/28 19:42:35 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 1;

static int	ft_readline_main(t_parse *parser, t_data *data)
{
	set_term_attr(TC_OFF);
	parser->rd_ln = readline("🔻minishell> ");
	if (g_sig == 0 && ++g_sig && !free_arr(&parser->rd_ln))
	{
		set_env(data, new_env("?=", "1", FORME));
		return (1);
	}
	set_term_attr(TC_ON);
	if (!parser->rd_ln && ft_putstr_fd("exit\n", 1, FREE_OFF))
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
