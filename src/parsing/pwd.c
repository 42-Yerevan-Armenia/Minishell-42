/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:18:59 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/31 18:13:48 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SHELL_INIT "shell-init: error retrieving current \
 directory: getcwd: cannot access parent directories: No such file or directory\n"

int	pwd(t_data *data)
{
	char	*ptr;
	char	*my_pwd;

	errno = 0;
	ptr = getcwd(NULL, 0);
	if (ptr == NULL && errno == ENOENT)
	{
		my_pwd = get_val(data->env->head, "MY_PWD");
		if (my_pwd)
			printf("%s\n", my_pwd);
		else
			ft_putstr_fd(SHELL_INIT, 2);
	}
	else
		printf("%s\n", ptr);
	free_arr(&ptr);
	return (0);
}
