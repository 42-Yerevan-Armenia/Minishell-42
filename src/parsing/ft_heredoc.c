/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:40:29 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/26 17:41:07 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_hiden_file(t_data *data, char **f_name)
{
	int		i;
	char	*doc;
	char	*path;
	int		fd;

	fd = -1;
	path = NULL;
	doc = ".42doc";
	i = 0;
	while (++i)
	{
		path = ft_strjoin_2(get_val(data->env->head, "TMPDIR"), ft_strjoin_2(doc, ft_itoa(i)));
		if (access(path, F_OK) && !free_arr(&path))
			break;
			free_arr(&path);
	}
	*f_name = ft_strjoin_2(get_val(data->env->head, "TMPDIR"), ft_strjoin_2(doc,
				ft_itoa(i)));
	fd = open(*f_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	// printf("f_name = %s\n", *f_name);
	if (fd == -1 && ft_perror("minishell"))
		return (-1);
	return (fd);
}

char	*ft_heredoc(t_spl_pipe *node, t_parse *parser)
{
	char	*res;
	char	*rd_ln;
	char	*ptr;
	int		i;
	char	*f_name;

	res = NULL;
	f_name = NULL;
	rd_ln = NULL;
	i = 0;
	while (node->heredoc[i])
	{
		free_arr(&rd_ln);
		while (1)
		{
			free_arr(&rd_ln);
			rd_ln = readline(">");
			if (!rd_ln && !ft_perror("minishell"))
				exit(1);
			if (res)
				res = ft_strjoin_1(res, "\n");
			if (node->heredoc[i] && !ft_strcmp(rd_ln, node->heredoc[i]))
				break ;
			res = ft_strjoin_1(res, rd_ln);
		}
		i++;
		free_arr(&rd_ln);
	}
	if (node->hdoc_mode == HDOC_DQ_MODE && res)
		rep_vars(parser, &res);
	ft_putstr_fd(res, create_hiden_file(parser->data, &f_name));
	free_arr(&rd_ln);
	free_arr(&res);

	return (f_name);
}
