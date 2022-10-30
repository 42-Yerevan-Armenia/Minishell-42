/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:18:59 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/30 11:16:02 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_data *data, char **args)
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
			ft_putstr_fd("shell-init: error retrieving current \
 directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
	}
	else
		printf("%s\n", ptr);
	free_arr(&ptr);
	return (0);
}
