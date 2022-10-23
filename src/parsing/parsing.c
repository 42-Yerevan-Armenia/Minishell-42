/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:46:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/23 18:09:47 by vaghazar         ###   ########.fr       */
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

int	get_files(char *tmp, t_spl_pipe *node, int *i, int c)
{
	static	int	k;
	static	int	m;
	static	int	h;
	static	int	n_cmd;
	int			j;

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
	// printf("*i = %d\n", *i);
		while (tmp[*i] && (tmp[*i] == '\'' || tmp[*i] == '"'))
		{
			j = (*i)++;
			while (tmp[*i] && tmp[*i] != tmp[j])
				*i += 1;
			(*i)++;
		}
	}
	else
	{
		while(tmp[*i] && (!ft_strchr(METACHARS, tmp[*i])/* || tmp[*i] == '\'' || tmp[*i] == '"')*/))
		{
			if (tmp[*i] == '\'' || tmp[*i] == '"')
				pass_qutoes(i, tmp);
			*i += 1;
		}
	}
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
	data->parser = parser;
	parser->spl_qutoes = NULL;
	parser->spl_pipe = NULL;
	parser->join_pipe = NULL;
	parser->rd_ln = NULL;
	parser->l_arr = 2;
	data->cmd_line = create_list_pipe();
	data->env = create_list_env();
	data->env_exp = create_list_env();
	data->exit_status = 0;
	get_env(&data->env, envp, ENV);
	get_env(&data->env_exp, envp, EXPORT);
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
	return (0);
}
// sdgsdgsd"     "dsgsdgsdg
int parsing(t_parse *parser)
{
	int	i = 0;
	split_quotes(parser);
	rep_vars(parser, NULL);
	split_pipe(parser);
	pipe_join(parser);
	get_all_hd_modes(parser);
	// while ( parser->data->hdoc_mode[i])
	// {
	// 	printf("mode = %d\n", parser->data->hdoc_mode[i++][0]);
	// }
	// while (parser->join_pipe[i])
	// {
	// 	printf("%s\n", parser->join_pipe[i]);
	// 	i++;
	// }
	find_exe(parser);
	ft_clean_all_qutoes(parser->data->cmd_line->head);
	get_hd_mode_int_pipe(parser);
	// create_rd_files(parser);
	// get_infile_fd(parser);
	if (parser->data->error_message)
		printf("%s", parser->data->error_message);
	print_info(parser);
	free_parse(parser);
	return (0);
}

char	**split_for_exp(char *str, char c, int *flag)
{
	char	**res;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * 3);
	fill_null((void *)&res, 3);
	while (str[i])
	{
		if (str[i] == c)
		{
			res[0] = ft_substr(str, 0, i);
			res[1] = ft_substr(str, i + 1, ft_strlen(str - i));
			*flag = 1;
			return (res);
		}
		i++;
	}
	res[0] = ft_strdup(str);
	return (res);
}

int	export(t_data *data, char **args)
{
	int	i;
	int	j;
	int flag;
	t_list_env *exp;
	char	**tmp;

	i = 1;
	flag = 0;
	exp = data->env_exp;
	if (args == NULL)
		return (1);
	if (args[i] == NULL)
	{
		print_exp(exp->head);
		return (0);
	}
	while (args[i])
	{
		tmp = split_for_exp(args[i], '=', &flag);
		// tmp = ft_split(args[i], '=');
		printf("%s\n", tmp[0]);
		printf("%s\n", tmp[1]);
		
		set_env(&exp, new_env(tmp[0], tmp[1], EXPORT));
		if (flag)
			set_env(&data->env, new_env(tmp[0], tmp[1], ENV));
		free_double(&tmp);
		// while (i == 1)
		// {
		// 	/* code */
		// }
		i++;
	}
	return (0);
}

int	env(t_data *data, char **args)
{
	int	i;
	int	j;
	t_list_env *env;
	char	**tmp;

	i = 1;
	env = data->env;
	if (args == NULL)
		return (1);
	if (args[i] == NULL)
	{
		print_env(env->head);
		return (0);
	}
	return (0);
}

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
		data.error_message = NULL;
		// print_env(data.env->head);
		// print_env(data.env_exp->head);
		while (1)
		{
			parser.rd_ln = readline("🔻minishell> ");
			if (!parser.rd_ln && !ft_perror("minishell"))
				exit (1);
			if (parser.rd_ln[0])
			{
				add_history(parser.rd_ln);
				parsing(&parser);
				// printf("%s\n", data.cmd_line->head->cmd);
				if (!ft_strcmp(data.cmd_line->head->cmd[0], "e"))
					export(&data, data.cmd_line->head->cmd);
				// if (!ft_strcmp(data.cmd_line->head->cmd[0], "env"))
				// 	env(&data, data.cmd_line->head->cmd);
				// printf("%s", ft_heredoc(data.cmd_line->head, &parser));
				// find_path(&data);
				free_spl_pipe(&data.cmd_line);
			}
			free_arr(&parser.rd_ln);
		}
		free_envp(&data.env);
	}
	// char c = '4';
	// char *ptr = &c;
	// printf("%p\n", *ptr + 100);
}




// int main(int ac, char **av)
// {
// 	export();
// }