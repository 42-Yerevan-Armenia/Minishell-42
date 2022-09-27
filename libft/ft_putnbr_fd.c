/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:30:52 by vaghazar          #+#    #+#             */
/*   Updated: 2022/03/17 21:30:53 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr2(int num, int size, int fd)
{
	while (size)
	{
		ft_putchar_fd((num / size) + '0', fd);
		num %= size;
		size /= 10;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int	num;
	int	size;

	size = 1;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n == -2147483648)
	{
		ft_putchar_fd('2', fd);
		n = 147483648;
	}
	num = n;
	while (num >= 10)
	{
		num = num / 10;
		size *= 10;
	}
	num = n;
	ft_putstr2(num, size, fd);
}
