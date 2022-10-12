/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:46:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/12 20:01:52 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  "<<hd'" |   kd|   dd|" dj $'* ><kkk -ld sdf"  rt' pwd|"$ho'|M
//  cat < b
//  cat <b <a<g<g

int	get_files(char *tmp, t_node *node, int *i, int c)
{
	static	int	k = 0;
	static	int	m = 0;
	static	int	h = 0;
	static	int	a = 0;
	int			j;
	// if (c == -1)
	// {
		
	// }
	while (ft_strchr(SPACES, tmp[*i]))
		*i+= 1;
	if (ft_strchr(METACHARS, tmp[*i]))
	{
		node->error_message = "syntax error\n";
		return (1);
	}
	j = *i;
	if ((tmp[j] == '\'' || tmp[j] == '"') && ++(*i))
	{
		while (tmp[*i] && ((tmp[*i] != '\'' && tmp[*i] != '"')))
			*i += 1;
		(*i)++;
	}
	else
		while(tmp[*i] && (!ft_strchr(METACHARS, tmp[*i])))
			*i+= 1;
		// printf("j = %d,i = %d\n", j, *i);
		// printf("j = %c,i = %c\n", tmp[j], tmp[*i]);
	if (c == HEARDOC)
		node->heardocs[h++] = ft_substr(tmp, j, *i - j);
	else if (c == APPEND_FILES)
		node->out_append_files[a++] = ft_substr(tmp, j, *i - j);
	else if (c == OUT_FILES)
		node->out_files[m++] = ft_substr(tmp, j, *i - j);
	else if (c == IN_FILES)
		node->in_files[k++] = ft_substr(tmp, j, *i - j);
	if (c == APPEND_FILES || c == OUT_FILES)
		node->output_mode = c;
	printf("k = %d, m = %d, a = %d, h = %d\n", k, m, a, h);
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
	printf("quantity->in_file = %d\n", quantity->in_file);
	node->in_files = malloc(quantity->in_file);
	node->out_files = malloc(quantity->out_file);
	node->heardocs = malloc(quantity->heardoc);
	node->out_append_files = malloc(quantity->heardoc);
	printf("node = %p\n", node);
	// printf("%d\n", node->out_files[0]);
	fill_null(node->in_files, quantity->in_file);
	fill_null(node->out_files, quantity->out_file);
	// printf("%d\n", node->out_files[0]);
	fill_null(node->heardocs, quantity->heardoc);
	fill_null(node->out_append_files, quantity->out_append_files);
	tmp = parser->rd_ln;
	while (tmp[i])
	{
		if (tmp[i] == '<' && tmp[i + 1] == '<' && ++i && ++i)
			get_files(tmp, node, &i, HEARDOC);
		else if (tmp[i] == '>' && tmp[i + 1] == '>' && ++i && ++i)
			get_files(tmp, node, &i, APPEND_FILES);
		else if (tmp[i] == '<' && ++i)
			get_files(tmp, node, &i, IN_FILES);
		else if (tmp[i] == '>' && ++i)
			get_files(tmp, node, &i, OUT_FILES);
		if (tmp[i] && !ft_strchr(HANDLE, tmp[i]))
			i++;
	}
	// get_files(tmp, node, &i, -1);
	return (0);
}




int parsing(t_parse *parser)
{
	int	i;
	// printf("%d\n", check_quote(parser));
	// split_quotes(parser);
	// int i = 0;

	// // while (parser->spl_qutoes[i])
	// // {
	// // 	printf("%s\n", parser->spl_qutoes[i++]);
	// // }
	// // printf("=-----------------\n");
	// split_pipe(parser);
	// i = 0;
	// // while (parser->spl_pipe[i])
	// // {
	// // 	printf("%s\n", parser->spl_pipe[i++]);
	// // }
	// // printf("=-----------------\n");
	// pipe_join(parser);
	// i = 0;
	// while (parser->join_pipe[i])
	// {
	// 	printf("%s\n", parser->join_pipe[i++]);
	// }
	find_exe(parser);
	t_node *tmp = parser->data->cmd_line->head;
	printf("head = %p\n", parser->data->cmd_line->head);
	if (parser->data->error_message)
		printf("%s", parser->data->error_message);
	i = 0;
	printf("in_files \n");
	while (tmp->in_files[i])
	{
		printf("%s\n", tmp->in_files[i++]);
	}
	i = 0;
	printf("out_files \n");
	while (tmp->out_files[i])
	{
		printf("%s\n", tmp->out_files[i++]);
	}
	i = 0;
	printf("heardoc \n");
	while (tmp->heardocs[i])
	{
		printf("%s\n", tmp->heardocs[i++]);
	}
	i = 0;
	printf("append \n");
	while (tmp->out_append_files[i])
	{
		printf("%s\n", tmp->out_append_files[i++]);
	}
	printf("mode = %d\n", tmp->output_mode);
	return (0);
}

int	init(t_parse *parser, t_data *data)
{
	parser->data = data;
	parser->data->cmd_line = create_list();
	return (0);
}

int main(int ac, char **av)
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