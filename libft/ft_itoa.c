/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:23:03 by vaghazar          #+#    #+#             */
/*   Updated: 2022/03/17 21:23:05 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnum(long num, int size, char *str)
{
	if (num < 0)
	{
		*str++ = '-';
		num = -num;
	}
	while (size)
	{
		*str++ = (num / size) + '0';
		num %= size;
		size /= 10;
	}
	*str = '\0';
}

void	change_positive(long *num, int *size)
{
	if (*num < 0)
	{
		*num = -*num;
		*size += 1;
	}
}

char	*ft_itoa(int n)
{
	int		size;
	long	num;
	long	numprint;
	char	*ptr;
	int		temp;

	temp = 1;
	num = n;
	numprint = n;
	size = 1;
	change_positive(&num, &size);
	while (num >= 10)
	{
		num = num / 10;
		temp *= 10;
		size++;
	}
	ptr = (char *) malloc(size + 1);
	if (ptr == 0)
		return (0);
	ft_putnum(numprint, temp, ptr);
	return (ptr);
}
