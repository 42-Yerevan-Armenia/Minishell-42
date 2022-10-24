/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:40:29 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/24 10:21:39 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_hiden_file(t_data *data, char **f_name)
{
	int		i;
	char	*doc;
	int		fd;

	fd = -1;
	doc = ".42doc";
	i = 0;
	while (!access(ft_strjoin(get_env_val(data->env, "TMPDIR"),
				ft_strjoin(doc, ft_itoa(i))), F_OK))
		i++;
	*f_name = ft_strjoin(get_env_val(data->env, "TMPDIR"), ft_strjoin(doc,
				ft_itoa(i)));
	fd = open(*f_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
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
	return (f_name);
}
