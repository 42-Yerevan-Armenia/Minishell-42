/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:44:26 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/19 12:06:34 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid(char	*str)
{
	int	i;

	i = 0;
	while (str[i] && ft_strchr(SPACES, str[i]))
		i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isdigit(str[i]) || i > 12)
			return (1);
		i++;
	}
	return (0);
}

int	shell_lvl(t_data *data)
{
	char	*tmp;
	char	*res;
	long	num;

	tmp = get_val(data->env->head, "SHLVL", ENV);
	if ((tmp == NULL || is_valid(tmp) == 1))
	{
		set_env(data, new_env("SHLVL=", "1", (ENV | EXPORT)));
		return (0);
	}
	num = ft_atoi(tmp);
	if (num == 999)
		set_env(data, new_env("SHLVL=", "", (ENV | EXPORT)));
	else if (num >= 1000 && ft_putstr_fd(ft_strjoin_1(ft_strjoin("🔻minishell:\
 warning: shell level (", tmp), ") too high, resetting to 1\n"), 2, FREE_ON))
		set_env(data, new_env("SHLVL=", "1", (ENV | EXPORT)));
	else
	{
		res = ft_itoa(num + 1);
		set_env(data, new_env("SHLVL=", res, (ENV | EXPORT)));
		free_arr(&res);
	}
	return (0);
}
