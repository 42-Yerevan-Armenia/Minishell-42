/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:18:59 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/15 19:24:25 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_data *data, t_spl_pipe *cur)
{
	char	*ptr;
	char	*my_pwd;

	errno = 0;
	ptr = getcwd(NULL, 0);
	if (ptr == NULL && errno == ENOENT)
	{
		my_pwd = get_val(data->env->head, "PWD", FORME);
		if (my_pwd)
			ft_putendl_fd(my_pwd, cur->fd_out, FREE_OFF);
		else
			ft_putstr_fd(SHELL_INIT, 2, FREE_OFF);
		// if (my_pwd)
		// 	printf("%s\n", my_pwd);
		// else
		// 	ft_putstr_fd(SHELL_INIT, 2, FREE_OFF);
	}
	else
		ft_putendl_fd(ptr, cur->fd_out, FREE_OFF);
		// printf("%s\n", ptr);
	free_arr(&ptr);
	return (0);
}
