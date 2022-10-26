/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:45:02 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/26 16:08:06 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	ft_strcmp_get_val(char *s1, char *s2)
// {
// 	while (*s1)
// 	{
// 		if (*s1 != *s2 || (*s1 && *(s1 + 1) == '='))
// 		{
// 			break ;
// 		}
// 		s1++;
// 		s2++;
// 	}
// 	return (*(unsigned char *)s1 - *(unsigned char *)s2);
// }

char	*get_val(t_env *head, char *key)
{
	while (key && head)
	{
		// printf("head->key = %s\n", head->key);
		// printf("key = %s\n", key);
		if (!ft_strcmp(head->key, key))
			return (head->val);
		head = head->next;
	}
	return (NULL);
}