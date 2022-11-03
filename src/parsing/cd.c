/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:28:18 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/03 20:22:13 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define CD_ERROR "minishell: cd: error retrieving current directory: getcwd: cannot access parent\
 directories: No such file or directory\n"

int	go_home(t_data *data)
{
	char	*tmp;

	tmp = get_val(data->env->head, "HOME");
	if (!tmp && ft_putstr_fd("minishell: cd: HOME not set\n", 2, FREE_OFF))
		return (1);
	else
	{
		if (chdir(tmp) == -1 && !ft_perror("minishel: cd :"))
			return (1);
		tmp = getcwd(NULL, 0);
		set_env(data, new_env("PWD", tmp, FORME));
		set_env(data, new_env("PWD", tmp, (ENV | EXPORT)));
		free_arr(&tmp);
	}
	return (0);
}

int	deleted_dir(t_data *data, char **args)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL && errno == ENOENT)
	{
		if (chdir(args[1]) == -1 && !ft_perror("minishell: cd: "))
			return (1);
		tmp = getcwd(NULL, 0);
		if (tmp && !free_arr(&tmp))
		{
			set_env(data, new_env("PWD", tmp, FORME));
			set_env(data, new_env("PWD", tmp, (ENV | EXPORT)));
		}
		else
		{
			set_env(data, new_env("PWD",
					ft_strjoin(ft_strjoin(get_val(data->env->head,
								"PWD"), "/"), args[1]), FORME));
			set_env(data, new_env("PWD", ft_strjoin(ft_strjoin(get_val(
								data->env->head, "PWD"), "/"),
						args[1]), (ENV | EXPORT)));
			ft_putstr_fd(CD_ERROR, 2, FREE_OFF);
		}
	}
	return (0);
}

int	normal_behave(t_data *data, char **args, char *tmp)
{
	if (chdir(args[1]) == -1 && !ft_perror("minishel: cd: "))
		return (1);
	tmp = getcwd(NULL, 0);
	set_env(data, new_env("PWD", tmp, FORME));
	set_env(data, new_env("PWD", tmp, (ENV | EXPORT)));
	free_arr(&tmp);
	return (0);
}

int	cd(t_data *data, char **args)
{
	char	*old_pwd;
	char	*tmp;

	tmp = NULL;
	old_pwd = get_val(data->env->head, "PWD");
	if (arr_double_len(args) == 1)
		go_home(data);
	else
	{
		tmp = getcwd(NULL, 0);
		if (tmp == NULL && errno == ENOENT)
		{
			if (deleted_dir(data, args) == 1)
				return (1);
		}
		else if (normal_behave(data, args, tmp) == 1)
			return (1);
	}
	set_env(data, new_env("OLDPWD", old_pwd, (ENV | EXPORT)));
	return (0);
}
