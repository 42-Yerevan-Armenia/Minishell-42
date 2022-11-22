/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:40:29 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/22 16:52:07 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_heredoc_rdln(char **rd_ln, char ***res)
{
	set_term_attr(TC_OFF);
	*rd_ln = readline("> ");
	set_term_attr(TC_ON);
	if (!*rd_ln)
		return (ENDF);
	if (g_sig == 0 && !free_double(res) && !free_arr(rd_ln) && ++g_sig)
		exit (SIGNAL);
	return (0);
}

static int	ft_heredoc_helper(t_spl_pipe **node, char **res, char	*rd_ln)
{
	int	i;

	i = -1;
	while ((*node)->heredoc[++i])
	{
		free_arr(res);
		while (!free_arr(&rd_ln))
		{
			ft_heredoc_rdln(&rd_ln, &res);
			if ((res && *res))
				*res = ft_strjoin_1(*res, "\n");
			if (rd_ln == NULL || ((*node)->heredoc[i]
					&& !ft_strcmp(rd_ln, (*node)->heredoc[i])))
				break ;
			*res = ft_strjoin_1(*res, rd_ln);
			free_arr(&rd_ln);
		}
		free_arr(&rd_ln);
	}
	return (0);
}

void	child(t_spl_pipe *node, t_parse *parser)
{
	char	*rd_ln;
	char	**res;

	rd_ln = NULL;
	res = malloc(sizeof(char *) * 2);
	fill_null((void *)&res, 2);
	ft_heredoc_helper(&node, res, rd_ln);
	parser->hered_res = res;
	if (node->hdoc_mode == HDOC_DQ_MODE && res)
		rep_vars(parser, HEREDOC);
	ft_putstr_fd(*res, node->fd_hdc, FREE_OFF);
	free_arr(&rd_ln);
	free_double((void *)&res);
	if (close(node->fd_hdc) == -1 && !ft_perror("minishell: close: "))
		exit (-1);
	exit(0);
}

int	parent(t_spl_pipe *node, int pid)
{
	int	res;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &res, 0);
	hook_signals();
	if (WEXITSTATUS(res) == SIGNAL)
	{
		node->data->exit_status = 1;
		return (START_RD_LN);
	}
	else
	{
		node->data->exit_status = 0;
		node->fd_hdc = open(node->f_name, O_RDWR);
	}
	return (0);
}

int	ft_heredoc(t_spl_pipe *node, t_parse *parser)
{
	int		pid;

	node->fd_hdc = create_hiden_file(parser->data, node, &node->f_name);
	if (node->fd_hdc == START_RD_LN)
		return (START_RD_LN);
	pid = fork();
	if (pid == -1)
		return (START_RD_LN);
	if (pid == 0)
		child(node, parser);
	else
	{
		if (parent(node, pid) == START_RD_LN)
			return (START_RD_LN);
	}
	return (node->fd_hdc);
}
