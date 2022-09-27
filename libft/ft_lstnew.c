/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:42:06 by vaghazar          #+#    #+#             */
/*   Updated: 2022/05/23 12:06:13 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int data)
{
	t_list	*ptr;

	ptr = malloc(sizeof(ptr));
	if (!ptr)
		return (0);
	ptr -> data = data;
	ptr -> index = -1;
	ptr -> next = NULL;
	return (ptr);
}
