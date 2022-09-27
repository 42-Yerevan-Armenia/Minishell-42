/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:19:31 by vaghazar          #+#    #+#             */
/*   Updated: 2022/03/26 11:35:37 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int argument)
{
	if (!((argument <= 122 && argument >= 97)
			|| (argument <= 90 && argument >= 65)
			|| (argument <= 57 && argument >= 48)))
	{
		return (0);
	}
	return (1);
}
