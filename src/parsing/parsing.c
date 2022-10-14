/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:46:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/14 10:59:05 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_files(char *tmp, t_node *node, int *i, int c)
{
	static	int	k = 0;
	static	int	m = 0;
	static	int	h = 0;
	static	int	a = 0;
	static	int	n_cmd = 0;
	int			j;
	while (ft_strchr(SPACES, tmp[*i]))
		*i+= 1;
	j = *i;
	if ((tmp[j] == '\'' || tmp[j] == '"') && ++(*i))
	{
		while (tmp[*i] && ((tmp[*i] != '\'' && tmp[*i] != '"')))
			*i += 1;
		(*i)++;
	}
	else
		while(tmp[*i] && (!ft_strchr(METACHARS, tmp[*i])))
			*i += 1;
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
int	fill_node(t_node *node, char *cmd_ln)
{
	int	i;
	i = 0;
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
 	t_node	*node;
 	t_elem	*quantity;
 	int		flag;
 	char	*tmp;
 	int		j;
 	int		k;

 	i = 0;
 	node = add_node(parser->data->cmd_line, NULL, NULL);
 	quantity = count_elem(parser->rd_ln);
 	node->in_files = malloc(sizeof(char *) * quantity->in_file);
 	node->out_files = malloc(sizeof(char *) * (quantity->out_file + quantity->out_append_files));
 	node->heredoc = malloc(sizeof(char *) * quantity->heredoc);
 	node->cmd = malloc(sizeof(char *) * 100);
 	fill_null(&node->cmd, 100);
 	fill_null(&node->in_files, quantity->in_file);
 	fill_null(&node->out_files, quantity->out_file);
 	fill_null(&node->heredoc, quantity->heredoc);
 	tmp = parser->rd_ln;
 	while (tmp[i])
 	{
 		if (tmp[i] == '<' && tmp[i + 1] == '<' && ++i && ++i)
 			get_files(tmp, node, &i, HEREDOC);
 		else if (tmp[i] == '>' && tmp[i + 1] == '>' && ++i && ++i)
 			get_files(tmp, node, &i, APPEND_FILES);
 		else if (tmp[i] == '<' && ++i)
 			get_files(tmp, node, &i, IN_FILES);
 		else if (tmp[i] == '>' && ++i)
 			get_files(tmp, node, &i, OUT_FILES);
 		else if (!ft_strchr(METACHARS, tmp[i]))
 			get_files(tmp, node, &i, COMAND);
 		if (tmp[i] && !ft_strchr(HANDLE, tmp[i]))
 			i++;
 	}
 	return (0);
 }

int	free_list(t_node *head)
{
	while (head)
	{
		free_double(&head->cmd);
		free_double(&head->out_files);
		free_double(&head->in_files);
		free_double(&head->heredoc);
		head = head->next;
		free(head->prev);
	}
	return (0);
}
 int parsing(t_parse *parser)
 {
 	int	i;
 	find_exe(parser);
 	t_node *tmp = parser->data->cmd_line->head;
	print_info(parser);
	free_parse(parser);
	return (0);
}
int	init(t_parse *parser, t_data *data)
{
	parser->data = data;
	parser->spl_qutoes = NULL;
	parser->spl_pipe = NULL;
	parser->join_pipe = NULL;
	parser->rd_ln = NULL;
	// data->cmd_line = NULL;
	parser->data->cmd_line = create_list();
	return (0);
}

/*
//  "<<hd'" |   kd|   dd|" dj $'* ><kkk -ld sdf"  rt' pwd|"$ho'|M
//  cat < b
//  cat <<b <a<g>t<g>r >>p -l -a "barev  "

int	get_files(char *tmp, t_node *node, int *i, int c)
{
	static	int	k = 0;
	static	int	m = 0;
	static	int	h = 0;
	static	int	a = 0;
	static	int	n_cmd = 0;
	int			j;

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
		while (tmp[*i] && ((tmp[*i] != '\'' && tmp[*i] != '"')))
			*i += 1;
		(*i)++;
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

int	fill_node(t_node *node, char *cmd_ln)
{
	int	i;

	i = 0;
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
	t_node	*node;
	t_elem	*quantity;
	int		flag;
	char	**tmp;
	int		j;
	int		k;

	i = 0;
	tmp = parser->join_pipe;
	// printf("%s\n", tmp[]);
	while (tmp[i])
	{
		node = add_node(parser->data->cmd_line, NULL, NULL);
		quantity = count_elem(tmp[i]);
		node->in_files = malloc(sizeof(char *) * quantity->in_file);
		node->out_files = malloc(sizeof(char *) * (quantity->out_file + quantity->out_append_files));
		node->heredoc = malloc(sizeof(char *) * quantity->heredoc);
		node->cmd = malloc(sizeof(char *) * 100);
		fill_null(&node->cmd, 100);
		fill_null(&node->in_files, quantity->in_file);
		fill_null(&node->out_files, quantity->out_file);
		fill_null(&node->heredoc, quantity->heredoc);
		fill_node(node, tmp[i++]);
	}
	
	return (0);
}

int	free_list(t_node *head)
{
	while (head)
	{
		free_double(&head->cmd);
		free_double(&head->out_files);
		free_double(&head->in_files);
		free_double(&head->heredoc);
		head = head->next;
		free(head->prev);
	}
	return (0);
}

int parsing(t_parse *parser)
{
	int	i;
	split_quotes(parser);
	split_pipe(parser);
	pipe_join(parser);
	find_exe(parser);
	t_node *tmp = parser->data->cmd_line->head;
	// if (parser->data->error_message)
	// 	printf("%s", parser->data->error_message);
	print_info(parser);
	free_parse(parser);
	return (0);
}

int	init(t_parse *parser, t_data *data)
{
	parser->data = data;
	parser->spl_qutoes = NULL;
	parser->spl_pipe = NULL;
	parser->join_pipe = NULL;
	parser->rd_ln = NULL;
	// data->cmd_line = NULL;
	parser->data->cmd_line = create_list();
	return (0);
}

int main1(int ac, char **av)
{
	t_parse parser;
	t_data	data;

	if (ac == 1)
	{
		init(&parser, &data);
		data.error_message = NULL;
		// while (1)
		// {
			parser.rd_ln = readline("minishell> ");
			parsing(&parser);
		// }
	}
	// int	i = 0;
	// int	*a = &i;

	// printf("%d, %p\n", *a, a);
	// (*a)++;
	// printf("%d, %p\n", *a, a);
	return (0);
}
*/





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