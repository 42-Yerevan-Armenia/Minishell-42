/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:46:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/29 19:52:15 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  "<<hd'" |   kd|   dd|" dj $'* ><kkk -ld sdf"  rt' pwd|"$ho'|M
//  cat < b
//  cat <<b <a<g>t<g>r >>p| -l -a "barev  "
// "$HOME $PWD" "$HOME"


void pass_qutoes(int *i, char *str)
{
	char tmp;

	tmp = str[(*i)++];
	while (str[*i] && str[*i] != tmp)
		(*i)++;
}
//  echo "barev"  "sdgsdg"
int	get_files(char *tmp, t_spl_pipe *node, int *i, int c)
{
	static	int	k;
	static	int	m;
	static	int	h;
	static	int	n_cmd;
	int			j;
	char		del;

	if (node->flag_new_pipe == 0 && ++(node->flag_new_pipe))
		init_zero(&k, &m, &h, &n_cmd);
	while (ft_strchr(SPACES, tmp[*i]))
		*i+= 1;
	// if (ft_strchr(METACHARS, tmp[*i]))
	// {
	// 	node->error_message = "syntax error\n";
	// 	return (1);
	// }
	j = *i;
	// printf("*i = %d\n", *i);
	if (tmp[*i] == '\'' || tmp[*i] == '"')
	{
		while (tmp[*i] && ((tmp[*i] == '\'' || tmp[*i] == '"')/* || !ft_strchr(SPACES, tmp[*i])*/))
		{
	// printf("*i = %d\n", *i);
			del = tmp[(*i)++];
			while (tmp[*i] && tmp[*i] != del)
				*i += 1;
			if (tmp[*i])
				*i += 1;
	// printf("1) *i = %d\n", *i);
	// printf("1) *i = %c\n", tmp[*i]);
			while (tmp[*i] && tmp[*i] != '\'' && tmp[*i] != '"' && !ft_strchr(METACHARS, tmp[*i]) && !ft_strchr(SPACES, tmp[*i]))
				*i += 1;
			if (tmp[*i] != '\'' && tmp[*i] != '"')
				break;
				// pass_qutoes(i, tmp);
	// printf("last *i = %d\n", *i);
		}
	}
	else
	{
		while(tmp[*i] && (!ft_strchr(METACHARS, tmp[*i])/* || tmp[*i] == '\'' || tmp[*i] == '"')*/))
		{
			if (tmp[*i] == '\'' || tmp[*i] == '"')
				pass_qutoes(i, tmp);
			// printf("%c\n", tmp[*i]);
			*i += 1;
		}
	}
			// printf("%d\n", j);
			// printf("%d\n", *i);
		// printf("j = %d,i = %d\n", j, *i);
		// printf("j = %c,i = %c\n", tmp[j], tmp[*i]);
	if (c == HEREDOC)
		node->heredoc[h++] = ft_substr(tmp, j, *i - j);
	else if (c == O_TRUNC || c == O_APPEND)
		node->out_files[m++] = ft_substr(tmp, j, *i - j);
	else if (c == IN_FILES)
		node->in_files[k++] = ft_substr(tmp, j, *i - j);
	else if (c == COMAND)
	{
		// printf("node->tmp = %d\n", node->tmp);
		// printf("node->tmp = %d\n", n_cmd);
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
		// printf("%s\n", cmd_ln);
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

int	find_exe(t_parse *parser)
{
	int		i;
	t_spl_pipe	*node;
	t_elem	*quantity;
	char	**tmp;
	int		j;
	int		k;

	i = 0;
	tmp = parser->join_pipe;
	while (tmp[i])
	{
		node = add_pipe(parser->data->cmd_line, new_spl_pipe(NULL, NULL));
		quantity = count_elem(tmp[i]);
		// printf("quantity->in_file = %d\n, quantity->out_file = %d\n, quantity->out_append_files = %d\n, quantity->heredoc %d\n", quantity->in_file, quantity->out_file, quantity->out_append_files, quantity->heredoc);
		node->in_files = malloc(sizeof(char *) * quantity->in_file);
		node->out_files = malloc(sizeof(char *) * (quantity->out_file + quantity->out_append_files));
		node->heredoc = malloc(sizeof(char *) * quantity->heredoc);
		node->cmd = malloc(sizeof(char *) * 100);
		if ((!node->in_files || !node->out_files || !node->heredoc || !node->cmd) && !ft_perror("minishell"))
			return (0);
		fill_null((void *)&node->cmd, 100);
		fill_null((void *)&node->in_files, quantity->in_file);
		fill_null((void *)&node->out_files, quantity->out_file + quantity->out_append_files);
		fill_null((void *)&node->heredoc, quantity->heredoc);
		fill_spl_pipe(node, tmp[i]);
		free(quantity);
		i++;
	}
	
	return (0);
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
	data->parser = parser;
	data->envp = NULL;
	data->hdoc_mode = NULL;
	data->cmd_line = create_list_pipe();
	data->env = create_list_env();
	data->env_exp = create_list_env();
	data->exit_status = 0;
	get_env(data, envp, (EXPORT | ENV));
	// get_env(data, envp, (ENV));
	char *pwd = getcwd(NULL, 0);
	set_env(data, new_env("PWD", pwd, (ENV | EXPORT)));
	set_env(data, new_env("MY_PWD", pwd, (FORME)));
	free_arr(&pwd);
	set_env(data, new_env("?", "0", (FORME)));
	// set_env(data, new_env("MY_PWD", getcwd(NULL, 0), (ENV | EXPORT)));
	data->envp =  env_cpy(data, data->env);
	return (0);
}

int get_hd_mode_int_pipe(t_parse *parser)
{
	t_spl_pipe *tmp;
	int			i;

	i = 0;
	tmp = parser->data->cmd_line->head;
	while (tmp && parser->data->hdoc_mode[i])
	{
		tmp->hdoc_mode = parser->data->hdoc_mode[i][0];
		i++;
		tmp = tmp->next;
	}
	free_double((void *)&parser->data->hdoc_mode);
	return (0);
}

int	unexpected_tokens(t_parse *parser)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = parser->rd_ln;
	while (tmp[i])
	{
		if (ft_strchr(UNEXPECTED, tmp[i]))
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

// sdgsdgsd"     "dsgsdgsdg

int parsing(t_parse *parser)
{
	int	i = 0;
	// if (unexpected_tokens(parser) == 1 && ft_putstr_fd("unexpected token\n",2))
	// 	return(1);
	split_quotes(parser);
	rep_vars(parser, NULL);
	split_pipe(parser);
	pipe_join(parser);
	get_all_hd_modes(parser);
	find_exe(parser);
	ft_clean_all_qutoes(parser->data->cmd_line->head);
	get_hd_mode_int_pipe(parser);
	// create_rd_files(parser);
	// get_infile_fd(parser);
	print_info(parser);
	return (0);
}

// int free_all()
// {
// 	free_spl_pipe
// }

int main(int ac, char **av, char **envp)
{
	t_parse parser;
	t_data	data;
	int i = 0;
	int j = 0;

	i = 0;
	if (ac == 1)
	{
		init(&parser, &data, envp);
		// data.error_message = NULL;
		while (1)
		{
// start:
			parser.rd_ln = readline("🔻minishell> ");
			if (!parser.rd_ln && !ft_perror("minishell"))
				exit (1);
			if (parser.rd_ln[0])
			{
				add_history(parser.rd_ln);
				if (parsing(&parser) == 1 && !free_arr(&parser.rd_ln))
					continue;
				if (!ft_strcmp(data.cmd_line->head->cmd[0], "export"))
					printf("exit = %d\n", export(&data,
								data.cmd_line->head->cmd));
				else if (!ft_strcmp(data.cmd_line->head->cmd[0], "env"))
					printf("exit = %d\n", env(&data, data.cmd_line->head->cmd));
				else if (!ft_strcmp(data.cmd_line->head->cmd[0], "echo"))
					printf("exit = %d\n", echo(&data, data.cmd_line->head->cmd));
				else if (!ft_strcmp(data.cmd_line->head->cmd[0], "unset"))
					printf("exit = %d\n", unset(&data, data.cmd_line->head->cmd));
				else if (!ft_strcmp(data.cmd_line->head->cmd[0], "pwd"))
					printf("exit = %d\n", pwd(&data, data.cmd_line->head->cmd));
				else if (!ft_strcmp(data.cmd_line->head->cmd[0], "cd"))
					printf("exit = %d\n", cd(&data, data.cmd_line->head->cmd));
				else
               		execute(&data);
				// printf("%s", ft_heredoc(data.cmd_line->head, &parser));
				// set_env(&data, new_env("?", ft_itoa(data.exit_status), FORME));
				free_spl_pipe(&data.cmd_line);
				free_parse(&parser);
			}
			free_arr(&parser.rd_ln);
		}
		free_envp(&data.env);
	}
}


// int main()
// {
// 	char *ptr;
// 	char buf[100];
// 	// printf("%ld\n", PATH_MAX);
// 	ptr = getcwd(buf, 100);

// 	printf("buf = %s\n", buf);
// 	printf("buf = %p\n", buf);
// 	printf("ptr = %s\n", ptr);
// 	printf("ptr = %p\n", ptr);
// 	ptr = getcwd(buf, 100);
// 	// ptr = getcwd(NULL, 0);
// 	printf("buf = %s\n", buf);
// 	printf("buf = %p\n", buf);
// 	printf("ptr = %s\n", ptr);
// 	printf("ptr = %p\n", ptr);
// 	while (1)
// 	{
// 		/* code */
// 	}
	
// }
