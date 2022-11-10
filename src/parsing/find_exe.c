/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:12:48 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/10 18:29:37 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_arrs(t_spl_pipe *node, char *tmp, t_vars *v)
{
	static int	m;
	static int	h;
	static int	n_cmd;
	static int	l_arr = 2;

	if (node->flag_new_pipe == 0 && ++(node->flag_new_pipe)
		&& !init_zero(&m, &h, &n_cmd, NULL))
		l_arr = 2;
	if (v->c == HEREDOC)
		node->heredoc[h++] = ft_substr(tmp, v->j, v->i - v->j);
	else if (v->c == COMAND && !resize_arr(&node->cmd, &l_arr, n_cmd))
		node->cmd[n_cmd++] = ft_substr(tmp, v->j, v->i - v->j);
	else
	{
		node->rdc[m] = ft_substr(tmp, v->j, v->i - v->j);
		if (node->rdc[m][0] == '\0' && !free_arr(&node->rdc[m]))
			node->rdc[m] = ft_strdup(BAD_RDR);
		else if (!clean_quotes_single_arr(&node->rdc[m]))
			ft_put_rdc_mode(&node->rdc[m], v->c);
		m++;
	}
	if (v->c == IN_FILES || v->c == HEREDOC)
		node->input_mode = v->c;
	return (0);
}

static void	starting_quotes(char *tmp, t_vars *v)
{
	char		del;

	while (tmp[v->i] && ((tmp[v->i] == '\'' || tmp[v->i] == '"')))
	{
		del = tmp[(v->i)++];
		while (tmp[v->i] && tmp[v->i] != del)
			v->i += 1;
		if (tmp[v->i])
			v->i += 1;
		while (tmp[v->i] && tmp[v->i] != '\'' && tmp[v->i] != '"'
			&& !ft_strchr(METACHARS, tmp[v->i])
			&& !ft_strchr(SPACES, tmp[v->i]))
			v->i += 1;
		if (tmp[v->i] != '\'' && tmp[v->i] != '"')
			break ;
	}
}

static int	get_files(char *tmp, t_spl_pipe *node, t_vars *v, int c)
{
	v->c = c;
	while (tmp[v->i] && ft_strchr(SPACES, tmp[v->i]))
		v->i += 1;
	v->j = v->i;
	if (tmp[v->i] == '\'' || tmp[v->i] == '"')
		starting_quotes(tmp, v);
	else
	{
		while (tmp[v->i] && (!ft_strchr(METACHARS, tmp[v->i])))
		{
			if (tmp[v->i] == '\'' || tmp[v->i] == '"')
				pass_qutoes(&v->i, tmp);
			v->i += 1;
		}
	}
	fill_arrs(node, tmp, v);
	return (0);
}

static int	fill_spl_pipe(t_spl_pipe *node, char *cmd_ln)
{
	t_vars	v;

	init_vars(&v, 0, 0, 0);
	node->flag_new_pipe = 0;
	while (cmd_ln[v.i])
	{
		if (cmd_ln[v.i] == '<' && cmd_ln[v.i + 1] == '<' && ++v.i && ++v.i)
			get_files(cmd_ln, node, &v, HEREDOC);
		else if (cmd_ln[v.i] == '>' && cmd_ln[v.i + 1] == '>' && ++v.i && ++v.i)
			get_files(cmd_ln, node, &v, APPEND_FILES);
		else if (cmd_ln[v.i] == '<' && ++v.i)
			get_files(cmd_ln, node, &v, IN_FILES);
		else if (cmd_ln[v.i] == '>' && ++v.i)
			get_files(cmd_ln, node, &v, OUT_FILES);
		else if (!ft_strchr(METACHARS, cmd_ln[v.i]))
			get_files(cmd_ln, node, &v, COMAND);
		if (cmd_ln[v.i] && !ft_strchr(HANDLE, cmd_ln[v.i]))
			v.i++;
	}
	return (0);
}

void	find_exe(t_parse *parser)
{
	t_spl_pipe	*node;
	t_elem		*qty;
	char		**tmp;
	int			i;

	tmp = parser->join_pipe;
	i = -1;
	while (tmp[++i])
	{
		node = add_pipe(parser->data->cmd_line, new_spl_pipe(parser->data));
		qty = count_elem(tmp[i]);
		node->heredoc = malloc(sizeof(char *) * qty->hdoc);
		node->rdc = malloc(sizeof(char *) * qty->rdc);
		node->cmd = malloc(sizeof(char *) * 3);
		if ((!node->heredoc || !node->rdc
				|| !node->cmd) && !ft_perror("minishell: "))
			exit (1);
		fill_null((void *)&node->cmd, 3);
		fill_null((void *)&node->heredoc, qty->hdoc);
		fill_null((void *)&node->rdc, qty->rdc);
		fill_spl_pipe(node, tmp[i]);
		free(qty);
	}
}
