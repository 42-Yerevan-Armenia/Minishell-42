/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:39:16 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/08 20:29:06 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_term(int signum)
{
	g_sig = 0;
	(void)signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

int	hook_signals(void)
{
	struct sigaction	term;

	term.sa_handler = &sig_term;
	term.sa_flags = SA_RESTART;
	term.sa_mask = 0;
	sigaction(SIGINT, &term, NULL);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
