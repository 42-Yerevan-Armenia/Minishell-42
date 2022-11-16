/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:25:49 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/16 21:02:38 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init(t_parse *parser, t_data *data, char **envp)
{
	parser->data = data;
	parser->l_arr = 2;
	parser->key = NULL;
	parser->spl_qutoes = NULL;
	parser->spl_pipe = NULL;
	parser->join_pipe = NULL;
	parser->rd_ln = NULL;
	parser->hered_res = NULL;
	data->parser = parser;
	data->envp = NULL;
	data->cmd_paths = NULL;
	data->path = NULL;
	data->hdoc_mode = NULL;
	data->cmd_line = create_list_pipe();
	data->env = create_list_env();
	data->env_exp = create_list_env();
	data->exit_status = 0;
	get_env(data, envp, (EXPORT | ENV));
	shell_lvl(data);
	return (0);
}
