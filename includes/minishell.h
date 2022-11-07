/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:31:58 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/07 17:52:28 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H



       // #include <readline/readline.h>
       // #include <readline/history.h>

# include "../libft/libft.h"
// # include "readline/readline.h"
# include "structs.h"
# include "defines.h"
# include "limits.h"
# include <errno.h>
# include <fcntl.h>
# include "readline/history.h"
# include "readline/readline.h"
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>


# include <sys/ioctl.h>
# include <termios.h>

# define WHITE	"\033[0;29m"
# define RED	"\033[1;31m"
# define GREEN	"\033[0;32m"
# define YELLOW	"\033[1;33m"
# define BLUE	"\033[1;34m"
# define PHILO	"\033[0;35m"
# define SKY	"\033[1;36m"

extern int	g_sig;

void			printf_header(void);
void			builtin_forking(t_data *data);
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
void			rep_vars(t_parse *parser, int flag);
void			get_env(t_data *data, char **envp, int is_export);
int				ft_heredoc(t_spl_pipe *node, t_parse *parser);
int				create_rd_files(t_spl_pipe *head, int *error);
int				get_infile_fd(t_spl_pipe *node, int	*error);
void			set_term_attr(int on_off);
int				shell_lvl(t_data *data);

// execute
int				execute(t_data *data);
int				run_builtins(t_data *data, t_spl_pipe *tmp);
void			pipe_redirections(t_spl_pipe *tmp);
void			open_pipes(t_spl_pipe *tmp, int i, int (*fds)[2], int psize);
void			close_fds(int (*fds)[2], t_spl_pipe *tmp, int psize);

// parsing
void			find_exe(t_parse *parser);
int				get_hd_mode_in_pipe(t_parse *parser);
int				ft_put_rdc_mode(char **s, int mode);
int				ft_get_rdc_mode(char *s);
int				unexpected_tokens(t_parse *parser);
int				check_quote(t_parse *parser);
int				ft_put_rdc_mode(char **s, int mode);
int				ft_get_rdc_mode(char *s);

// builtins
int				echo(char **args);
int				export(t_data *data, char **args);
int				unset(t_data *data, char **args);
int				env(t_data *data, char **args);
int				pwd(t_data *data);
int				cd(t_data *data, char **args);
int				ft_exit(t_data *data, char **args);
int				run_heredoc(t_data *data);

// helper func
t_list_spl_pipe	*create_list_pipe(void);
t_spl_pipe		*new_spl_pipe(t_data *data);
t_spl_pipe		*add_pipe(t_list_spl_pipe *list, t_spl_pipe *new_pipe);
int				fill_null(void ***ptr, int len);
int				resize_arr(char ***arr, int *l_arr, int k);
char			*ft_strchrs(const char *s, const char *set);
t_elem			*count_elem(char *str);
void			print_info(t_parse *parser);
int				free_double(char ***ptr);
int				free_parse(t_parse *parser);
int				free_spl_pipe(t_list_spl_pipe **list);
int				init_zero(int *ptr1, int *ptr2, int *ptr3, int *ptr4);
int				free_envp(t_list_env **list);
int				free_arr(char **arr);
int				ft_perror(char *str);
// int				count_quotes(char *arr);
// int 			clean_quotes(char ***arr);
int				ft_clean_all_qutoes(t_spl_pipe *head);
int				clean_quotes_single_arr(char **s);
// int             find_hdoc_mode(char *str);
int				get_all_hd_modes(t_parse *parser);
size_t			arr_double_len(char **arr);
char			*ft_strjoin_1(char *s1, char *s2);
char			*ft_strjoin_2(char *s1, char *s2);
char			*ft_strjoin_all(char **str);
void			init_vars(t_vars *v, int i, int j, int k);
void			pass_qutoes(int *i, char *str);

// env api
t_list_env		*create_list_env(void);
t_env			*new_env(char *key, char *val, int is_export);
void			set_env(t_data *data, t_env *new_node);
int				del_env_node(t_list_env *env, char *key);
// char			*get_env_val(t_list_env *env, char *key);
int				print_env_rev(t_env *tail);
char			**split_for_env(char *str, char c);
char			**env_cpy(t_data *data, t_list_env *env);
int				del_one(t_env **env);
int				find_var_rap(t_list_env *env, t_env *new_node);

// utils

void			print_env_arr(char **env);
void	pipes(t_data *data, int psize, t_spl_pipe *tmp);
void	do_cmd(t_data *data, t_spl_pipe *tmp, int psize);

#endif

// need error keys for pipe and fork
// fds did not closed after cat | cat | cat ...
// do not see infile and outfile

//dzem sax

// free_all for exit