/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:40:29 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/04 22:05:37 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_hiden_file(t_data *data, t_spl_pipe *node, char **f_name)
{
	int		i;
	char	*doc;
	char	*path;

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
	node->fd_hdc = open(*f_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (node->fd_hdc == -1 && ft_perror("minishell: "))
		return (START_RD_LN);
	return (node->fd_hdc);
}

static int	ft_heredoc_helper(t_spl_pipe **node, char **res, char	*rd_ln)
{
	int	i;

	i = -1;
	while ((*node)->heredoc[++i])
	{
		free_arr(&rd_ln);
		while (1)
		{
			free_arr(&rd_ln);
			// set_term_attr(TC_OFF);
			rd_ln = readline(">");
			if (g_sig == 0 && ++g_sig)
				return (1);
			// set_term_attr(TC_ON);
			if (!rd_ln && !ft_perror("minishell: "))
				exit(1);
			if (res && *res)
				*res = ft_strjoin_1(*res, "\n");
			if ((*node)->heredoc[i] && !ft_strcmp(rd_ln, (*node)->heredoc[i]))
				break ;
			*res = ft_strjoin_1(*res, rd_ln);
		}
		free_arr(&rd_ln);
	}
	return (0);
}

int	ft_heredoc(t_spl_pipe *node, t_parse *parser)
{
	char	**res;
	char	*rd_ln;
	int		fd;

	rd_ln = NULL;
	res = malloc(sizeof(char *) * 2);
	fill_null((void *)&res, 2);
	if (ft_heredoc_helper(&node, res, rd_ln) == 1)
		return (START_RD_LN);
	parser->hered_res = res;
	if (node->hdoc_mode == HDOC_DQ_MODE && res)
		rep_vars(parser, HEREDOC);
	fd = create_hiden_file(parser->data, node, &node->f_name);
	ft_putstr_fd(*res, fd, FREE_OFF);
	free_arr(&rd_ln);
	free_double((void *)&res);
	return (fd);
}
