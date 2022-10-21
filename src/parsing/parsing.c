/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:46:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/20 19:46:15 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  "<<hd'" |   kd|   dd|" dj $'* ><kkk -ld sdf"  rt' pwd|"$ho'|M
//  cat < b
//  cat <<b <a<g>t<g>r >>p| -l -a "barev  "
// "$HOME $PWD" "$HOME"

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
	if ((tmp[j] == '\'' || tmp[j] == '"') && ++(*i))
	{
		j = *i;
		while (tmp[*i] && tmp[*i] != tmp[j - 1])
			*i += 1;
	}
	else
		while(tmp[*i] && (!ft_strchr(METACHARS, tmp[*i])))
			*i += 1;
		// printf("j = %d,i = %d\n", j, *i);
		// printf("j = %c,i = %c\n", tmp[j], tmp[*i]);
	if (c == HEREDOC)
		node->heredoc[h++] = ft_substr(tmp, j, *i - j);
	else if (c == OUT_FILES || c == APPEND_FILES)
		node->out_files[m++] = ft_substr(tmp, j, *i - j);
	else if (c == IN_FILES)
		node->in_files[k++] = ft_substr(tmp, j, *i - j);
	else if (c == COMAND)
		node->cmd[n_cmd++] = ft_substr(tmp, j, *i - j);
	if (c == APPEND_FILES || c == OUT_FILES)
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
			get_files(cmd_ln, node, &i, APPEND_FILES);
		else if (cmd_ln[i] == '<' && ++i)
			get_files(cmd_ln, node, &i, IN_FILES);
		else if (cmd_ln[i] == '>' && ++i)
			get_files(cmd_ln, node, &i, OUT_FILES);
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
		fill_null(&node->cmd, 100);
		fill_null(&node->in_files, quantity->in_file);
		fill_null(&node->out_files, quantity->out_file + quantity->out_append_files);
		fill_null(&node->heredoc, quantity->heredoc);
		fill_spl_pipe(node, tmp[i]);
		free(quantity);
		i++;
	}
	
	return (0);
}

int	init(t_parse *parser, t_data *data, char **envp)
{
	parser->data = data;
	parser->spl_qutoes = NULL;
	parser->spl_pipe = NULL;
	parser->join_pipe = NULL;
	parser->rd_ln = NULL;
	data->cmd_line = create_list_pipe();
	data->env = create_list_env();
	data->env_exp = create_list_env();
	data->exit_status = 0;
	get_env(&data->env, envp, ENV);
	get_env(&data->env_exp, envp, EXPORT);
	return (0);
}

int parsing(t_parse *parser)
{
	int	i = 0;
	split_quotes(parser);
	rep_vars(parser);
	split_pipe(parser);
	pipe_join(parser);
	// while (parser->spl_qutoes[i])
	// {
	// 	printf("%s\n", parser->spl_qutoes[i]);
	// 	i++;
	// }
	find_exe(parser);
	if (parser->data->error_message)
		printf("%s", parser->data->error_message);
	print_info(parser);
	free_parse(parser);
	return (0);
}

size_t	arr_double_len(char	**arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

// int	export(t_data *data, char **args)
// {
// 	int	i;

// 	i = 0;
// 	if (arr_double_len(args) == 1)
// 		return (1);
// 	while (args[i])
// 	{
// 		/* code */
// 	}
	
// 	return (0);
// }


// int main(int ac, char **av)
// {
// 	int fd;
// 		// fd = open("barev", O_RDONLY);
// 		// printf("%s\n", strerror(errno));
// 		// char *str = strerror(errno);
// 		// perror("minishell");
// 	if (ac != 1)
// 	{
// 		export(NULL, av);
// 		// echo(NULL, av);
// 	}
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
				// find_path(&data);
					// parser.data->cmd_line->head->hdoc_input = ft_heredoc(&parser, parser.data->cmd_line->head->heredoc[i]);
				free_spl_pipe(&data.cmd_line);
			}
			free_arr(&parser.rd_ln);
		}
		free_envp(&data.env);
	}
}



// int	check_syntax(t_parse *parser)
// {
// 	char	*tmp;
// 	int		i;

// 	tmp = parser->rd_ln;
// 	i = 0;
// 	while (tmp[i])
// 	{
// 		if (tmp[i] == '|')
// 		{
// 			if (tmp[i + 1] == '|' || tmp[i + 1] == '\0')
// 				return (1);
// 			while (tmp[i])
// 			{
				
// 				i++;
// 			}
			
// 		}
// 		i++;
// 	}
// 	return (0);
// }