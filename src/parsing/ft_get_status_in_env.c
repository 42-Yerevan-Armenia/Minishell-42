/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_status_in_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:31:14 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/26 13:20:05 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_status_in_env(t_data *data, t_parse *parser)
{
	char	*status;

	status = ft_itoa(data->exit_status);
	set_env(data, new_env("?=", status, FORME));
	free_arr(&status);
	free_double(&data->cmd_paths);
	free_spl_pipe(&data->cmd_line);
	free_parse(parser);
	return (0);
}
