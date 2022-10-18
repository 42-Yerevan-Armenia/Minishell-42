/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:31:58 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/15 18:54:12 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "structs.h"

void pipex(t_data *data);

void    dis_prompt();
int     split_quotes(t_parse *parser);
int     split_pipe(t_parse *parser);
int     pipe_join(t_parse *parser);
void    find_path(t_data *data);
int parsing(t_parse *parser);
int	init(t_parse *parser, t_data *data, char **envp);


// helper func
t_list_spl_pipe *create_list_pipe(void);
t_spl_pipe  *new_spl_pipe(void  *arg1, void *arg2);
t_spl_pipe *add_pipe(t_list_spl_pipe *list, t_spl_pipe *new_pipe);
int     fill_null(char ***ptr, int len);
char	**resize_arr(char **arr, int *l_arr);
char	*ft_strchrs(const char *s, const char *set);
t_elem  *count_elem(char *str);
void	print_info(t_parse *parser);
int     free_double(char ***ptr);
int     free_parse(t_parse *parser);
t_spl_pipe  *new_spl_pipe(void  *arg1, void *arg2);
int     free_spl_pipe(t_list_spl_pipe **list);
t_list_envp *create_list_envp(void);
void	init_zero(int *ptr1, int *ptr2, int *ptr3, int *ptr4);
int	free_envp(t_list_envp **list);


#endif

