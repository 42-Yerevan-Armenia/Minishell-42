/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:17:49 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/18 21:29:03 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;

	ptr = (char *) malloc(size * nmemb);
	if (ptr == 0 && !ft_perror("minishell"))
		return (0);
	ft_bzero(ptr, (nmemb * size));
	return (ptr);
}
