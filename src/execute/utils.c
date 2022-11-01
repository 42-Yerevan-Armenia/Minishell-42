/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 09:21:55 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/01 10:19:45 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pass_qutoes(int *i, char *str)
{
	char	tmp;

	tmp = str[(*i)++];
	while (str[*i] && str[*i] != tmp)
		(*i)++;
}

void	print_list(t_spl_pipe *head)
{
	while (head)
	{
		printf("%s, ", head->cmd[0]);
		printf("%s\n", head->cmd[1]);
		head = head->next;
	}
}

int	ft_perror(char *str)
{
	perror(str);
	return (0);
}
