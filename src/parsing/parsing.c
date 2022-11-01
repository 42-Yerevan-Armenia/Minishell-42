/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:46:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/01 10:23:34 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		g_sig[2] = {0, 0};

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
	parser->hered_vars = malloc(sizeof(char *) * 2);
	fill_null((void *)&parser->hered_vars, 2);
	data->parser = parser;
	data->envp = NULL;
	data->hdoc_mode = NULL;
	data->cmd_line = create_list_pipe();
	data->env = create_list_env();
	data->env_exp = create_list_env();
	data->exit_status = 0;
	// get_env(data, envp, (EXPORT | ENV));
	return (0);
}

int	get_hd_mode_in_pipe(t_parse *parser)
{
	t_spl_pipe	*tmp;
	int			i;

	i = 0;
	tmp = parser->data->cmd_line->head;
	while (tmp && parser->data->hdoc_mode[i])
	{
		tmp->hdoc_mode = parser->data->hdoc_mode[i][0];
		i++;
		tmp = tmp->next;
	}
	// free_double(&parser->data->hdoc_mode);
	return (0);
}

// int	empty_input(t_parse *parser)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	tmp = parser->rd_ln;
// 	while (tmp[i])
// 	{

// 		i++;
// 	}

// }

int	unexpected_tokens(t_parse *parser)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = parser->rd_ln;
	while (ft_strchr(SPACES, tmp[i]))
		i++;
	if (ft_strchr(UNEXPECTED, tmp[i]) && ft_putstr_fd(PIPE, 2))
	{
		// if (tmp[i] == )
		return (START_RD_LN);
	}
	while (tmp[i])
	{
		if (ft_strchr(UNEXPECTED, tmp[i]) && ++i)
		{
			while (ft_strchr(SPACES, tmp[i]))
				i++;
			if (ft_strchr(UNEXPECTED, tmp[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

// int	error_hendling(t_parse *parser)
// {
// 	return (0);
// }

int free_all(t_data *data)
{
	free_spl_pipe((void *)&data->cmd_line);

	free_parse((void *)&data->parser);
	free_arr(&data->parser->rd_ln);
	return (0);
}
int		run_heredoc(t_data *data);

int	parsing(t_parse *parser)
{
	int	i;

	i = 0;
	// if (unexpected_tokens(parser) == START_RD_LN
	// /*&& ft_putstr_fd("unexpected token\n",2)*/)
		// return(START_RD_LN);
	split_quotes(parser);
	rep_vars(parser, 0);
	split_pipe(parser);
	pipe_join(parser);
	get_all_hd_modes(parser);
	find_exe(parser);
	ft_clean_all_qutoes(parser->data->cmd_line->head);
	get_hd_mode_in_pipe(parser);
	print_info(parser);
	if (run_heredoc(parser->data) == START_RD_LN
		|| create_rd_files(parser) == START_RD_LN)
		return (START_RD_LN);
	return (0);
}




// void	sig_term(int signum)
// {
// 	struct termios	termios_p;

// 	// tcgetattr(0, &termios_p);
// 	// termios_p.c_lflag |= ECHOCTL;
// 	// tcsetattr(0, 0, &termios_p);
// 	g_sig = 0;
// 	(void)signum;
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	ioctl(STDIN_FILENO, TIOCSTI, "\n");
// 	// rl_replace_line("", 0);
// 	// rl_on_new_line();
// }

// int	hook_signals(void)
// {
// 	struct sigaction	term;

// 	term.sa_handler = &sig_term;
// 	term.sa_flags = SA_RESTART;
// 	term.sa_mask = 0;
// 	sigaction(SIGINT, &term, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// 	return (0);
// }

int	main(int ac, char **av, char **envp)
{
	t_parse	parser;
	t_data	data;

	(void)av;
	if (ac == 1)
	{
		init(&parser, &data, envp);
		// hook_signals();
		while (1)
		{
			set_term_attr(TC_OFF);
			parser.rd_ln = readline("🔻minishell> ");
			if (g_sig == 0 && ++g_sig)
				set_term_attr(TC_ON);
			if (!parser.rd_ln)
			{
				// rl_replace_line("", 0);
				// ft_putstr_fd("exit\n", 0);
				// rl_on_new_line();
				// rl_redisplay();
				exit(1);
			}
			if (parser.rd_ln[0])
			{
				add_history(parser.rd_ln);
				if (parsing(&parser) == START_RD_LN && !free_arr(&parser.rd_ln))
					continue ;
	// printf("")
	// printf("%d\n", data.cmd_line->head);
	// printf("%d\n", data.cmd_line->head->cmd);
	// sleep(1);
				// if (data.cmd_line->head->cmd[0])
				// {
				// 	execute(&data);
				// }

			}
				// set_env(&data, new_env("?", ft_itoa(data.exit_status), FORME));
			// free_spl_pipe(&data.cmd_line);
			// free_parse(&parser);
			// free_arr(&parser.rd_ln);
		}
		free_envp(&data.env);
	}
}
