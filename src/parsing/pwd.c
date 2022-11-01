/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:18:59 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/01 20:27:10 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_data *data)
{
	char	*ptr;
	char	*my_pwd;

	errno = 0;
	ptr = getcwd(NULL, 0);
	if (ptr == NULL && errno == ENOENT)
	{
		my_pwd = get_val(data->env->head, "PWD");
		if (my_pwd)
			printf("%s\n", my_pwd);
		else
			ft_putstr_fd(SHELL_INIT, 2, FREE_OFF);
	}
	else
		printf("%s\n", ptr);
	free_arr(&ptr);
	return (0);
}
