/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:46:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/07 21:37:59 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 1;

int	init(t_parse *parser, t_data *data, char **envp)
{
	parser->data = data;
	parser->l_arr = 2;
	parser->key = NULL;
	parser->spl_qutoes = NULL;
	parser->spl_pipe = NULL;
	parser->join_pipe = NULL;
	parser->rd_ln = NULL;
	parser->hered_res = NULL;
	data->parser = parser;
	data->envp = NULL;
	data->hdoc_mode = NULL;
	data->cmd_line = create_list_pipe();
	data->env = create_list_env();
	data->env_exp = create_list_env();
	data->exit_status = 0;
	get_env(data, envp, (EXPORT | ENV));
	shell_lvl(data);
	data->envp = env_cpy(data, data->env);
	return (0);
}

int	ft_get_status_in_env(t_data *data, t_parse *parser)
{
	char	*status;

	status = ft_itoa(data->exit_status);
	set_env(data, new_env("?", status, FORME));
	free_arr(&status);
	free_spl_pipe(&data->cmd_line);
	free_arr(&parser->rd_ln);
	free_parse(parser);
	return (0);
}

int	parsing(t_parse *parser)
{
	if (((check_quote(parser) == 1)
			|| (unexpected_tokens(parser) == START_RD_LN))
		&& !put_exit_s(parser->data, 258))
		return (START_RD_LN);
	split_quotes(parser);
	rep_vars(parser, 0);
	split_pipe(parser);
	pipe_join(parser);
	get_all_hd_modes(parser);
	find_exe(parser);
	if (parser->data->cmd_line->head == NULL)
		return (START_RD_LN);
	ft_clean_all_qutoes(parser->data->cmd_line->head);
	print_info(parser);
	get_hd_mode_in_pipe(parser);
	if ((run_heredoc(parser->data) == START_RD_LN))
		return (START_RD_LN);
	free_parse(parser);
	return (0);
}

int	ft_readline_main(t_parse *parser, t_data *data)
{
	set_term_attr(TC_OFF);
	parser->rd_ln = readline("🔻minishell> ");
	if (g_sig == 0 && ++g_sig && !free_arr(&parser->rd_ln))
	{
		set_env(data, new_env("?", "1", FORME));
		return (1);
	}
	set_term_attr(TC_ON);
	if (!parser->rd_ln)
		exit(1);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_parse	parser;
	t_data	data;
	
	(void)av;
	data.builtins =  ft_bultins();
	if (ac == 1)
	{
		init(&parser, &data, envp);
		hook_signals();
		while (!free_arr(&parser.rd_ln))
		{
			if (ft_readline_main(&parser, &data) == 1)
				continue ;
			if (parser.rd_ln[0])
			{
				add_history(parser.rd_ln);
				if (parsing(&parser) == START_RD_LN
					&& !ft_get_status_in_env(&data, &parser))
					continue ;
				if (data.cmd_line->head && data.cmd_line->head->cmd)
					execute(&data);
			}
			ft_get_status_in_env(&data, &parser);
		}
		free_envp(&data.env);
	}
}

