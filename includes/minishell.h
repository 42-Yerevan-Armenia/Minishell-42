/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:31:58 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/10 19:08:38 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include "structs.h"

void    dis_prompt();
void    add_node(t_list *list, char *cmd, char *options);
t_list *create_list(void);
int     split_quotes(t_parse *parser);
int     split_pipe(t_parse *parser);
char	**resize_arr(char **arr, int *l_arr);
int     pipe_join(t_parse *parser);

#endif

