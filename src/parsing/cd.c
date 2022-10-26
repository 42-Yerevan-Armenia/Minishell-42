/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:28:18 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/26 21:28:26 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cd(t_data *data, char **args)
{
	int i;

	i = 0;
	if (!args)
		return (1);
	set_env(&data->env, new_env("OLDPWD", get_val(data->env->head, "PWD"), ENV));
	chdir(args[1]);
	char *ptr = getcwd(NULL, 100);
	if (!ptr && errno == ENOENT)
		set_env(&data->env, new_env("PWD", get_val(data->env->head, args[1]), ENV));
	else if (!ptr && ft_perror("minishell"))
		return (1);
	else
		set_env(&data->env, new_env("PWD", ptr, ENV));
	return (0);
}
