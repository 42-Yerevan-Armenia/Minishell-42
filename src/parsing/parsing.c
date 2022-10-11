/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:46:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/11 18:52:37 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  "<<hd'" |   kd|   dd|" dj $'* ><kkk -ld sdf"  rt' pwd|"$ho'|M
//  cat < b
//  cat <<b

int	get_files(char *tmp, t_data *data, int *i, int c)
{
	static	int	k = 0;
	static	int	m = 0;
	static	int	h = 0;
	int			j;
	
	while (ft_strchr(SPACES, tmp[*i]))
		*i+= 1;
	if (ft_strchr(METACHARS, tmp[*i]))
	{
		data->error_message = "syntax error\n";
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
	if (c == -1)
		data->heardocs[h++] = ft_substr(tmp, j, *i - j);
	else if (c == '<')
		data->in_files[k++] = ft_substr(tmp, j, *i - j);
	else if (c == '>')
		data->out_files[m++] = ft_substr(tmp, j, *i - j);
	return (0);
}

int	find_exe(t_parse *parser, t_data *data)
{
	int		i;
	int		flag;
	char	*tmp;
	int		j;
	int		k;

	i = 0;
	flag = 0;
	k = 0;
	data->in_files = malloc(100);
	data->out_files = malloc(100);
	data->heardocs = malloc(100);
	fill_null(data->in_files, 100);
	fill_null(data->out_files, 100);
	fill_null(data->heardocs, 100);
	tmp = parser->rd_ln;
	while (tmp[i])
	{
		if (tmp[i] == '<' && tmp[i + 1] == '<' && ++i && ++i)
			get_files(tmp, data, &i, -1);
		else if (tmp[i] == '<' && ++i)
			get_files(tmp, data, &i, tmp[i - 1]);
		else if (tmp[i] == '>' && ++i)
			get_files(tmp, data, &i, tmp[i - 1]);
		if (tmp[i] && !ft_strchr(HANDLE, tmp[i]))
			i++;
	}
	return (0);
}

int parsing(t_parse *parser, t_data *data)
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
	find_exe(parser, data);
	if (data->error_message)
	printf("%s", data->error_message);
	i = 0;
	printf("in_files \n");
	while (data->in_files[i])
	{
		printf("%s\n", data->in_files[i++]);
	}
	
	i = 0;
	printf("out_files \n");
	while (data->out_files[i])
	{
		printf("%s\n", data->out_files[i++]);
	}
	i = 0;
	printf("heardoc \n");
	while (data->heardocs[i])
	{
		printf("%s\n", data->heardocs[i++]);
	}
	return (0);
}

int main(int ac, char **av)
{
	t_parse parser;
	t_data	data;

	if (ac == 1)
	{
		data.error_message = NULL;
		// while (1)
		// {
			parser.rd_ln = readline("minishell> ");
			parsing(&parser, &data);
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