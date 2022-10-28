/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:31:58 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/28 11:33:00 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <string.h>

int				pipex(int ac, char **av);
// char *ft_heredoc(t_parse *parser, char *dlmtr);

void			dis_prompt(void);
int				split_quotes(t_parse *parser);
int				split_pipe(t_parse *parser);
int				pipe_join(t_parse *parser);
void			find_path(t_data *data);
int				parsing(t_parse *parser);
int				init(t_parse *parser, t_data *data, char **envp);
char			*get_val(t_env *head, char *key);
char			*find_var(char *src, char **ptr, int j);
char			*ft_replace(t_parse *parser, char *src, int *j, char *k_ptr);
int				rep_vars(t_parse *parser, char **str);
// t_env			*get_env(t_list_env **env_list, char **envp, int is_export);
void	        get_env(t_data *data, char **envp, int is_export);
// char	*ft_heredoc(t_parse *parser, char *dlmtr);
char			*ft_heredoc(t_spl_pipe *node, t_parse *parser);
int				create_rd_files(t_parse *parser);
int				get_infile_fd(t_parse *parser);


// execute
int    execute(t_data *data);

// builtins
int				echo(t_data *data, char **args);
int				export(t_data *data, char **args);
int             unset(t_data *data, char **args);
int             env(t_data *data, char **args);
int             pwd(t_data *data, char **args);
int             cd(t_data *data, char **args);

// helper func
t_list_spl_pipe	*create_list_pipe(void);
t_spl_pipe		*new_spl_pipe(void *arg1, void *arg2);
t_spl_pipe		*add_pipe(t_list_spl_pipe *list, t_spl_pipe *new_pipe);
int				fill_null(void ***ptr, int len);
char			**resize_arr(char **arr, int *l_arr);
char			*ft_strchrs(const char *s, const char *set);
t_elem			*count_elem(char *str);
void			print_info(t_parse *parser);
int				free_double(void ***ptr);
int				free_parse(t_parse *parser);
t_spl_pipe		*new_spl_pipe(void *arg1, void *arg2);
int				free_spl_pipe(t_list_spl_pipe **list);
void			init_zero(int *ptr1, int *ptr2, int *ptr3, int *ptr4);
int				free_envp(t_list_env **list);
int				free_arr(char **arr);
int				ft_perror(char *str);
// int				count_quotes(char *arr);
// int 			clean_quotes(char ***arr);
int				ft_clean_all_qutoes(t_spl_pipe *head);
// int             find_hdoc_mode(char *str);
int				get_all_hd_modes(t_parse *parser);
size_t			arr_double_len(char **arr);
char			*ft_strjoin_1(char *s1, char *s2);
char            *ft_strjoin_2(char *s1, char *s2);
char			*ft_strjoin_all(char **str);

// env api
t_list_env		*create_list_env(void);
t_env			*new_env(char *key, char *val, int is_export);
void            set_env(t_data *data, t_env *new_node);
int				del_env_node(t_list_env *env, char *key);
// char			*get_env_val(t_list_env *env, char *key);
int				print_env(t_env *head);
int				print_exp(t_env *head);
int				print_env_rev(t_env *tail);
char            **split_for_env(char *str, char c);
char            **env_cpy(t_data *data, t_list_env *env);


// utils

void print_env_arr(char **env);

#endif