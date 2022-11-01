/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:27:59 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/01 20:11:11 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_for_env(char *str, char c)
{
	char	**res;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * 3);
	fill_null((void *)&res, 3);
	while (str[i])
	{
		if (str[i] == c)
		{
			res[0] = ft_substr(str, 0, i + 1);
			res[1] = ft_substr(str, i + 1, ft_strlen(str) - i);
			return (res);
		}
		i++;
	}
	res[0] = ft_strdup(str);
	return (res);
}

void	get_env(t_data *data, char **envp, int is_export)
{
	t_env	*env;
	char	**tmp;
	int		i;
	char	*pwd;

	i = 0;
	while (envp[i])
	{
		tmp = split_for_env(envp[i], '=');
		if (ft_strcmp(tmp[0], "OLDPWD="))
		{
			env = new_env(tmp[0], tmp[1], is_export);
			set_env(data, env);
		}
		i++;
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL && errno == ENOENT)
		ft_putstr_fd(SHELL_INIT, 2, FREE_OFF);
	set_env(data, new_env("PWD", pwd, (FORME)));
	set_env(data, new_env("OLDPWD", NULL, (EXPORT)));
	free_arr(&pwd);
	set_env(data, new_env("?", "0", (FORME)));
	data->envp = env_cpy(data, data->env);
}
