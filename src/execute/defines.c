/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:19:00 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/11 20:30:06 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	not_found(t_spl_pipe *tmp, t_data *data)
{
	ft_putstr_fd(ft_strjoin_2("🔻minishell> ", \
	ft_strjoin(*tmp->cmd, NOT_FOUND)), 2, FREE_ON);
	data->exit_status = 127;
}

void	is_dir(t_spl_pipe *tmp, t_data *data)
{
	ft_putstr_fd(ft_strjoin_2("🔻minishell> ", \
	ft_strjoin(*tmp->cmd, IS_DIR)), 2, FREE_ON);
	data->exit_status = 126;
}

void	no_dir(t_spl_pipe *tmp, t_data *data)
{
	ft_putstr_fd(ft_strjoin_2("🔻minishell> ", \
	ft_strjoin(*tmp->cmd, NO_DIR)), 2, FREE_ON);
	data->exit_status = 127;
}

void	no_perm(t_spl_pipe *tmp, t_data *data)
{
	ft_putstr_fd(ft_strjoin_2("🔻minishell> ", \
	ft_strjoin(*tmp->cmd, NO_PERM)), 2, FREE_ON);
	data->exit_status = 126;
}
