/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:46:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/31 21:52:28 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		g_sig[2] = {0, 0};
int		g_sig = 1;

void	pass_qutoes(int *i, char *str)
{
	char	tmp;

	tmp = str[(*i)++];
	while (str[*i] && str[*i] != tmp)
		(*i)++;
}
int	get_files(char *tmp, t_spl_pipe *node, int *i, int c)
{
	static int	k;
	static int	m;
	static int	h;
	static int	n_cmd;
	int			j;
	char		del;

	if (node->flag_new_pipe == 0 && ++(node->flag_new_pipe))
		init_zero(&k, &m, &h, &n_cmd);
	while (ft_strchr(SPACES, tmp[*i]))
		*i += 1;
	j = *i;
	if (tmp[*i] == '\'' || tmp[*i] == '"')
	{
		while (tmp[*i] && ((tmp[*i] == '\'' || tmp[*i] == '"') /*
					|| !ft_strchr(SPACES, tmp[*i])*/
							))
		{
			del = tmp[(*i)++];
			while (tmp[*i] && tmp[*i] != del)
				*i += 1;
			if (tmp[*i])
				*i += 1;
			while (tmp[*i] && tmp[*i] != '\'' && tmp[*i] != '"'
				&& !ft_strchr(METACHARS, tmp[*i]) && !ft_strchr(SPACES,
				tmp[*i]))
				*i += 1;
			if (tmp[*i] != '\'' && tmp[*i] != '"')
				break ;
		}
	}
	else
	{
		while (tmp[*i] && (!ft_strchr(METACHARS, tmp[*i]) /* || tmp[*i] == '\''
				|| tmp[*i] == '"')*/
							))
		{
			if (tmp[*i] == '\'' || tmp[*i] == '"')
				pass_qutoes(i, tmp);
			*i += 1;
		}
	}
	if (c == HEREDOC)
		node->heredoc[h++] = ft_substr(tmp, j, *i - j);
	else if (c == O_TRUNC || c == O_APPEND)
		node->out_files[m++] = ft_substr(tmp, j, *i - j);
	else if (c == IN_FILES)
		node->in_files[k++] = ft_substr(tmp, j, *i - j);
	else if (c == COMAND)
	{
		// if (node->tmp == n_cmd)
		// 	resize_arr(node->cmd, &node->tmp);
		node->cmd[n_cmd++] = ft_substr(tmp, j, *i - j);
	}
	if (c == O_APPEND || c == O_TRUNC)
		node->output_mode = c;
	else if (c == IN_FILES || c == HEREDOC)
		node->input_mode = c;
	return (0);
}

int	fill_spl_pipe(t_spl_pipe *node, char *cmd_ln)
{
	int	i;

	i = 0;
	node->flag_new_pipe = 0;
	while (cmd_ln[i])
	{
		if (cmd_ln[i] == '<' && cmd_ln[i + 1] == '<' && ++i && ++i)
			get_files(cmd_ln, node, &i, HEREDOC);
		else if (cmd_ln[i] == '>' && cmd_ln[i + 1] == '>' && ++i && ++i)
			get_files(cmd_ln, node, &i, O_APPEND);
		else if (cmd_ln[i] == '<' && ++i)
			get_files(cmd_ln, node, &i, IN_FILES);
		else if (cmd_ln[i] == '>' && ++i)
			get_files(cmd_ln, node, &i, O_TRUNC);
		else if (!ft_strchr(METACHARS, cmd_ln[i]))
			get_files(cmd_ln, node, &i, COMAND);
		if (cmd_ln[i] && !ft_strchr(HANDLE, cmd_ln[i]))
			i++;
	}
	return (0);
}

t_spl_pipe	*find_exe(t_parse *parser)
{
	int			i;
	t_spl_pipe	*node;
	t_elem		*quantity;
	char		**tmp;

	i = 0;
	tmp = parser->join_pipe;
	while (tmp[i])
	{
		node = add_pipe(parser->data->cmd_line, new_spl_pipe());
		quantity = count_elem(tmp[i]);
		node->in_files = malloc(sizeof(char *) * quantity->in_file);
		node->out_files = malloc(sizeof(char *) * (quantity->out_file
					+ quantity->out_append_files));
		node->heredoc = malloc(sizeof(char *) * quantity->heredoc);
		node->cmd = malloc(sizeof(char *) * 100);
		if ((!node->in_files || !node->out_files || !node->heredoc
				|| !node->cmd) && !ft_perror("minishell: "))
			exit (1);
		fill_null((void *)&node->cmd, 100);
		fill_null((void *)&node->in_files, quantity->in_file);
		fill_null((void *)&node->out_files, quantity->out_file
				+ quantity->out_append_files);
		fill_null((void *)&node->heredoc, quantity->heredoc);
		fill_spl_pipe(node, tmp[i]);
		free(quantity);
		i++;
	}
	return (parser->data->cmd_line->head);
}

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
		// write(1, "||||||\n", 9);
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
	if (find_exe(parser) == NULL && !free_all(parser->data))
		return (START_RD_LN);
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
