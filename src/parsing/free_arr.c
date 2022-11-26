/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:29:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/26 13:20:00 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_arr(char **arr)
{
	if (*arr)
	{
		free(*arr);
		*arr = NULL;
	}
	return (0);
}

int	free_double(char ***ptr)
{
	int	i;

	i = 0;
	if (*ptr == NULL)
		return (0);
	while ((*ptr) && ((*ptr))[i])
	{
		free(((*ptr))[i]);
		((*ptr))[i++] = NULL;
	}
	if (((*ptr)))
		free(((*ptr)));
	((*ptr)) = NULL;
	return (0);
}

int	free_all(t_data *data)
{
	free_envp(&data->env);
	free_envp(&data->env_exp);
	free_double(&data->builtins);
	free_double(&data->envp);
	free_double(&data->cmd_paths);
	free_spl_pipe(&data->cmd_line);
	free_parse(data->parser);
	free(data->cmd_line);
	free(data->env);
	free(data->env_exp);
	return (0);
}
