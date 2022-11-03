/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:12:48 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/03 19:09:30 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_put_rdc_mode(char **s, int mode)
{
	int		i;
	char	*res;
	char	*tmp;

	if (*s == NULL)
		return (1);
	i = 0;
	tmp = *s;
	res = malloc(ft_strlen(*s) + 3);
	while (*tmp)
		res[i++] = *tmp++;
	res[i++] = '\0';
	res[i++] = mode;
	res[i] = '\0';
	*s = res;
	return (0);
}

int	ft_get_rdc_mode(char *s)
{
	int		i;

	if (s == NULL || *s == '\0' || !ft_strcmp(s, BAD_RDR))
		return (1);
	i = 0;
	while (s[i])
		i++;
	i++;
	if (s[i] == OUT_FILES)
		return (O_TRUNC);
	if (s[i] == APPEND_FILES)
		return (O_APPEND);
	return (s[i]);
}

// int main()
// {
// 	char *s = "barev";

// 	ft_put_rdc_mode(&s, 8);
// 	printf("%d\n", ft_get_rdc_mode(s));
// }

static int	fill_arrs(t_spl_pipe *node, char *tmp, t_vars *v)
{
	static int	m;
	static int	h;
	static int	n_cmd;
	static int	l_arr = 2;

	if (node->flag_new_pipe == 0 && ++(node->flag_new_pipe))
	{
		l_arr = 2;
		init_zero(&m, &h, &n_cmd, NULL);
	}
	if (v->c == HEREDOC)
		node->heredoc[h++] = ft_substr(tmp, v->j, v->i - v->j);
	else if (v->c == COMAND && !resize_arr(&node->cmd, &l_arr, n_cmd))
	{
		node->cmd[n_cmd] = ft_substr(tmp, v->j, v->i - v->j);
		n_cmd++;
	}
	else
	{
		node->rdc[m] = ft_substr(tmp, v->j, v->i - v->j);
		if (node->rdc[m][0] == '\0')
			node->rdc[m] = ft_strdup(BAD_RDR);
		else if (!clean_quotes_single_arr(&node->rdc[m]))
			ft_put_rdc_mode(&node->rdc[m], v->c);
		m++;
	}
	if (v->c == IN_FILES || v->c == HEREDOC)
		node->input_mode = v->c;
	return (0);
}

// static int	fill_arrs(t_spl_pipe *node, char *tmp, t_vars *v)
// {
// 	static int	k;
// 	static int	m;
// 	static int	h;
// 	static int	n_cmd;
// 	static int	l_arr = 2;

// 	if (node->flag_new_pipe == 0 && ++(node->flag_new_pipe))
// 	{
// 		l_arr = 2;
// 		init_zero(&k, &m, &h, &n_cmd);
// 	}
// 	if (v->c == HEREDOC)
// 		node->heredoc[h++] = ft_substr(tmp, v->j, v->i - v->j);
// 	else if (v->c == O_TRUNC || v->c == O_APPEND)
// 		node->out_files[m++] = ft_substr(tmp, v->j, v->i - v->j);
// 	else if (v->c == IN_FILES)
// 		node->in_files[k++] = ft_substr(tmp, v->j, v->i - v->j);
// 	else if (v->c == COMAND && !resize_arr(&node->cmd, &l_arr, n_cmd))
// 		node->cmd[n_cmd++] = ft_substr(tmp, v->j, v->i - v->j);
// 	if (v->c == O_APPEND || v->c == O_TRUNC)
// 		node->output_mode = v->c;
// 	else if (v->c == IN_FILES || v->c == HEREDOC)
// 		node->input_mode = v->c;
// 	return (0);
// }

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

static int	fill_spl_pipe(t_parse *parser, t_spl_pipe *node, char *cmd_ln)
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

// export .a .b .c

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
		node = add_pipe(parser->data->cmd_line, new_spl_pipe());
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
		fill_spl_pipe(parser, node, tmp[i]);
		free(qty);
	}
}
