/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:31:58 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/14 10:53:37 by vaghazar         ###   ########.fr       */
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
int     split_quotes(t_parse *parser);
int     split_pipe(t_parse *parser);
int     pipe_join(t_parse *parser);

// helper func
t_list  *create_list(void);
t_node  *add_node(t_list *list, char *cmd, char *options);
int     fill_null(char ***ptr, int len);
char	**resize_arr(char **arr, int *l_arr);
char	*ft_strchrs(const char *s, const char *set);
t_elem  *count_elem(char *str);
void	print_info(t_parse *parser);
int     free_double(char ***ptr);
int     free_parse(t_parse *parser);


#endif

