/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 09:19:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/15 19:32:00 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_env(t_env *head, t_spl_pipe *cur)
{
	while (head)
	{
		if (head->is_export == ENV || head->is_export == (ENV | EXPORT))
			ft_putendl_fd(ft_strjoin(head->key, head->val),
				cur->fd_out, FREE_ON);
		head = head->next;
	}
	return (0);
}

int	env(t_spl_pipe *cur, char **args)
{
	int			i;
	t_list_env	*env;

	i = 1;
	env = cur->data->env;
	if (args == NULL)
		return (1);
	if (args[i] == NULL)
	{
		print_env(env->head, cur);
		return (0);
	}
	return (0);
}
