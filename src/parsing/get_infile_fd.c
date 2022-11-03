/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infile_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:33:28 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/03 13:56:51 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	get_infile_fd(t_spl_pipe *node, int *error)
// {
// 	int			i;
// 	int			fd;
// 	t_spl_pipe	*tmp;

// 	i = 0;
// 	tmp = node;
// 	if (node->f_name)
// 	{
// 		close(tmp->fd_in);
// 		unlink(node->f_name);
// 	}
// 	while (tmp->in_files[i])
// 	{
// 		if (tmp->out_files[i] == NULL && ft_putstr_fd(BAD_RDR, 2, FREE_OFF))
// 			return (START_RD_LN);
// 		if (i != 0)
// 			if (close(tmp->fd_in) == -1 && ft_perror("minishell: "))
// 				return (START_RD_LN);
// 		fd = open(tmp->in_files[i], O_RDONLY);
// 		if (tmp->fd_in == -1 && ft_perror("minishell: "))
// 			return (START_RD_LN);
// 		if (node->input_mode == IN_FILES)
// 			tmp->fd_in = fd;
// 		i++;
// 	}
// 	return (0);
// }
