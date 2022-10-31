/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:40:29 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/31 12:02:58 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_hiden_file(t_data *data, t_spl_pipe *node, char **f_name)
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
		path = ft_strjoin_2(get_val(data->env->head, "TMPDIR"),
				ft_strjoin_2(doc, ft_itoa(i)));
		if (access(path, F_OK) && !free_arr(&path))
			break ;
		free_arr(&path);
	}
	*f_name = ft_strjoin_2(get_val(data->env->head, "TMPDIR"), ft_strjoin_2(doc,
				ft_itoa(i)));
	printf("f_name = %p\n", *f_name);
	fd = open(*f_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1 && ft_perror("minishell: "))
		return (START_RD_LN);
	node->fd_in = fd;
	return (fd);
}

static void	ft_heredoc_helper(t_spl_pipe **node, char **res, char	*rd_ln)
{
	int	i;

	i = 0;
	while ((*node)->heredoc[i])
	{
		free_arr(&rd_ln);
		while (1)
		{
			free_arr(&rd_ln);
			rd_ln = readline(">");
			if (!rd_ln && !ft_perror("minishell: "))
				exit(1);
			if (*res)
				*res = ft_strjoin_1(*res, "\n");
			if ((*node)->heredoc[i] && !ft_strcmp(rd_ln, (*node)->heredoc[i]))
				break ;
			*res = ft_strjoin_1(*res, rd_ln);
		}
		i++;
		free_arr(&rd_ln);
	}
}

int	ft_heredoc(t_spl_pipe *node, t_parse *parser, int *error)
{
	char	**res;
	char	*rd_ln;

	res = parser->hered_vars;
	rd_ln = NULL;
	ft_heredoc_helper(&node, res, rd_ln);
	if (node->hdoc_mode == HDOC_DQ_MODE && res)
		rep_vars(parser, HEREDOC);
	*error = create_hiden_file(parser->data, node, &node->f_name);
	ft_putstr_fd(*res, *error);
	free_arr(&rd_ln);
	free_double((void *)&res);
	return (0);
}
