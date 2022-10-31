/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_term_attr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 20:25:37 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/31 20:26:19 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_term_attr(int on_off)
{
	struct termios	termios_p;

	tcgetattr(0, &termios_p);
	if (on_off == TC_OFF)
	{
		termios_p.c_lflag &= ~ECHOCTL;
		tcsetattr(0, 0, &termios_p);
	}
	else if (on_off == TC_ON)
	{
		termios_p.c_lflag |= ECHOCTL;
		tcsetattr(0, 0, &termios_p);
	}
}
