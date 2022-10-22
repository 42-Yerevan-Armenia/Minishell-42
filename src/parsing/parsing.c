/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:46:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/22 21:09:38 by vaghazar         ###   ########.fr       */
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
	// if ((tmp[j] == '\'' || tmp[j] == '"') && ++(*i))
	// {
	// 	j = *i;
	// 	while (tmp[*i] && tmp[*i] != tmp[j - 1])
	// 		*i += 1;
	// }
	// else
		while(tmp[*i] && (!ft_strchr(METACHARS, tmp[*i])))
			*i += 1;
		// printf("j = %d,i = %d\n", j, *i);
		// printf("j = %c,i = %c\n", tmp[j], tmp[*i]);
	if (c == HEREDOC)
		node->heredoc[h++] = ft_substr(tmp, j, *i - j);
	else if (c == O_TRUNC || c == O_APPEND)
		node->out_files[m++] = ft_substr(tmp, j, *i - j);
	else if (c == IN_FILES)
		node->in_files[k++] = ft_substr(tmp, j, *i - j);
	else if (c == COMAND)
		node->cmd[n_cmd++] = ft_substr(tmp, j, *i - j);
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

// int ft_clean_all_qutoes(t_spl_pipe *head)
// {
// 	while (head)
// 	{
// 		clean_quotes(&head->cmd);
// 		printf("%s\n", head->cmd[0]);
// 		clean_quotes(&head->heredoc);
// 		clean_quotes(&head->in_files);
// 		clean_quotes(&head->out_files);
// 		head = head->next;
// 	}
// 	return (0);
// }

int	is_single_qutoe(char *str)
{
	int	i;

	i = 0;
	while (str[i] &&  ft_strchr(SPACES, str[i]))
		i++;
	if (str[i] == '\'')
		return (HDOC_MODE);
	return (0);
}

int	find_hdoc_mode(char *str)
{
	int i;
	char	*tmp;

	i = 0;
	tmp = str;
	while (tmp[i])
	{
		if (tmp[i] == '<' && tmp[i + 1] == '<' && is_single_qutoe(str + i + 2))
			return (HDOC_MODE);
		i++;
	}
	return (0);
}

int parsing(t_parse *parser)
{
	int	i = 0;
	split_quotes(parser);
	rep_vars(parser);
	split_pipe(parser);
	pipe_join(parser);
	// find_hdoc_mode(parser);
	clean_quotes(&parser->join_pipe);
	// while (parser->spl_pipe[i])
	// {
	// 	printf("%s\n", parser->spl_pipe[i]);
	// 	i++;
	// }
	// clean_quotes(&parser->data->cmd_line->head->heredoc);
	find_exe(parser);
	// ft_clean_all_qutoes(parser->data->cmd_line->head);
	// create_rd_files(parser);
	// get_infile_fd(parser);
	if (parser->data->error_message)
		printf("%s", parser->data->error_message);
	print_info(parser);
	free_parse(parser);
	return (0);
}

// size_t	arr_double_len(char	**arr)
// {
// 	size_t	i;

// 	i = 0;
// 	while (arr && arr[i])
// 		i++;
// 	return (i);
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
				// printf("%s", ft_heredoc(&parser, data.cmd_line->head->heredoc[0]));
				// find_path(&data);
				free_spl_pipe(&data.cmd_line);
			}
			free_arr(&parser.rd_ln);
		}
		free_envp(&data.env);
	}
}
