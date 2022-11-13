/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:18:59 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/12 19:21:19 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_forme(t_env *head)
{
	while (head)
	{
		if (head->is_export == FORME)
			printf("FORME = %s%s\n", head->key, head->val);
		head = head->next;
	}
}

int	pwd(t_data *data)
{
	char	*ptr;
	char	*my_pwd;

	errno = 0;
	ptr = getcwd(NULL, 0);
	print_forme(data->env->head);
	if (ptr == NULL && errno == ENOENT)
	{
		my_pwd = get_val(data->env->head, "PWD", FORME);
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
