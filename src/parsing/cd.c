/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:28:18 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/11 16:43:20 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go_home(t_data *data)
{
	char	*tmp;

	tmp = get_val(data->env->head, "HOME", ENV);
	if (!tmp && ft_putstr_fd("minishell: cd: HOME not set\n", 2, FREE_OFF))
		return (1);
	else
	{
		if (chdir(tmp) == -1 && !ft_perror("minishel: cd : "))
			return (1);
		tmp = getcwd(NULL, 0);
		set_env(data, new_env("PWD=", tmp, FORME));
		if (get_node(data->env->head, "PWD", ENV) != NULL)
			set_env(data, new_env("PWD=", tmp, (ENV | EXPORT)));
		free_arr(&tmp);
	}
	return (0);
}

static void	deleted_dir_helper(t_data *data, char **args)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp)
	{
		set_env(data, new_env("PWD=", tmp, FORME));
		if (get_val(data->env->head, "PWD", ENV) != NULL)
			set_env(data, new_env("PWD=", tmp, (ENV | EXPORT)));
		free_arr(&tmp);
	}
	else
	{
		tmp = ft_strjoin_1(ft_strjoin(get_val
					(data->env->head, "PWD", FORME), "/"), args[1]);
		set_env(data, new_env("PWD=", tmp, FORME));
		if (get_val(data->env->head, "PWD", ENV) != NULL)
			set_env(data, new_env("PWD=", tmp, (ENV | EXPORT)));
		ft_putstr_fd(CD_ERROR, 2, FREE_OFF);
	}
	free_arr(&tmp);
}

int	deleted_dir(t_data *data, char **args)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL && errno == ENOENT)
	{
		if (chdir(args[1]) == -1 && ft_putstr_fd(ft_strjoin_1(ft_strjoin
					("minishell: cd: ", args[1]), NO_SUCH_F), 2, FREE_ON))
			return (1);
		free_arr(&tmp);
		deleted_dir_helper(data, args);
	}
	return (0);
}

int	normal_behave(t_data *data, char **args, char *tmp)
{
	if (chdir(args[1]) == -1 && ft_putstr_fd(ft_strjoin_1(
				ft_strjoin("minishell: cd: ", args[1]), NO_SUCH_F), 2, FREE_ON))
		return (1);
	tmp = getcwd(NULL, 0);
	set_env(data, new_env("PWD=", tmp, FORME));
	if (get_val(data->env->head, "PWD", ENV) != NULL)
		set_env(data, new_env("PWD=", tmp, (ENV | EXPORT)));
	free_arr(&tmp);
	return (0);
}

int	cd(t_data *data, char **args)
{
	char	*old_pwd;
	char	*tmp;

	tmp = NULL;
	old_pwd = get_val(data->env->head, "PWD", FORME);
	if (old_pwd != NULL)
		set_env(data, new_env("OLDPWD=", ft_strdup(old_pwd), (ENV | EXPORT)));
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
		else if (normal_behave(data, args, tmp) == 1 && !free_arr(&tmp))
			return (1);
		free_arr(&tmp);
	}
	return (0);
}
