/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:31:58 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/22 13:47:18 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "structs.h"
# include "defines.h"
# include "limits.h"
# include <errno.h>
# include <fcntl.h>
# include "readline/history.h"
# include "readline/readline.h"
# include <readline/history.h>
# include <readline/readline.h>
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

int				init(t_parse *parser, t_data *data, char **envp);
void			printf_header(void);
void			builtin_forking(t_data *data);
void			dis_prompt(void);
int				split_quotes(t_parse *parser);
int				split_pipe(t_parse *parser);
int				pipe_join(t_parse *parser);
void			find_path(t_data *data);
int				parsing(t_parse *parser);
int				init(t_parse *parser, t_data *data, char **envp);
char			*get_val(t_env *head, char *key, int mode);
t_env			*get_node(t_env *head, char *key, int mode);
char			*find_var(char *src, char **ptr, int j, char *next);
char			*ft_replace(t_parse *parser, char *src, int *j, char *k_ptr);
void			rep_vars(t_parse *parser, int flag);
void			get_env(t_data *data, char **envp, int is_export);
int				ft_heredoc(t_spl_pipe *node, t_parse *parser);
int				create_rd_files(t_spl_pipe *head, t_data *data);
int				get_infile_fd(t_spl_pipe *node, int	*error);
void			set_term_attr(int on_off);
int				shell_lvl(t_data *data);

// execute
void			cmd_errors_1(t_data *data, t_spl_pipe *tmp);
int				cmd_errors_2(t_data *data, t_spl_pipe *tmp);
int				cmd_errors(t_data *data, t_spl_pipe *tmp);
void			execute(t_data *data);
int				run_binar(t_data *data);
int				run_builtins(t_data *data, t_spl_pipe *tmp);
char			*get_cmd(char **paths, char *cmd);
void			pipex(int (*fds)[2], int psize);
void			pid_check(int (*fds)[2], int psize, int i, \
				t_spl_pipe *tmp, t_data *data);
void			open_pipes(t_spl_pipe *tmp, int i, int (*fds)[2], int psize);
int				close_fds(int (*fds)[2], int psize);
int				ft_get_status_in_env(t_data *data, t_parse *parser);

// parsing
int				parsing(t_parse *parser);
void			find_exe(t_parse *parser);
int				get_hd_mode_in_pipe(t_parse *parser);
int				ft_put_rdc_mode(char **s, int mode);
int				ft_get_rdc_mode(char *s);
int				unexpected_tokens(t_parse *parser);
int				check_quote(t_parse *parser);
int				ft_put_rdc_mode(char **s, int mode);
int				ft_get_rdc_mode(char *s);
char			*set_mode(char *s);

// builtins
int				ft_free(char **str);
char			*numstr(char *str);
// int				echo(char **args);
int				echo(t_spl_pipe *cur, char **args);
// int				export(t_data *data, char **args);
int				export(t_data *data, char **args, t_spl_pipe *cur);
int				unset(t_data *data, char **args);
int				env(t_spl_pipe *cur, char **args);
// int				env(t_data *data, char **args);
// int				pwd(t_data *data);
int				pwd(t_data *data, t_spl_pipe *cur);
int				cd(t_data *data, char **args);
void			ft_exit(t_data *data, char **args, t_spl_pipe *cur);
int				run_heredoc(t_data *data);
int				search_builtin(char *s, char **builtins);
char			**ft_bultins(void);

// helper func
t_list_spl_pipe	*create_list_pipe(void);
t_spl_pipe		*new_spl_pipe(t_data *data);
t_spl_pipe		*add_pipe(t_list_spl_pipe *list, t_spl_pipe *new_pipe);
int				fill_null(void ***ptr, int len);
int				resize_arr(char ***arr, int *l_arr, int k);
char			*ft_strchrs(const char *s, const char *set);
t_elem			*count_elem(char *str);
int				free_double(char ***ptr);
int				free_parse(t_parse *parser);
int				free_spl_pipe(t_list_spl_pipe **list);
int				init_zero(int *ptr1, int *ptr2, int *ptr3, int *ptr4);
int				free_envp(t_list_env **list);
int				free_arr(char **arr);
int				ft_perror(char *str);
int				ft_clean_all_qutoes(t_spl_pipe *head);
int				clean_quotes_single_arr(char **s);
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
int				set_env(t_data *data, t_env *new_node);
int				del_env_node(t_list_env *env, char *key, int mode);
int				print_env_rev(t_env *tail);
char			**split_for_env(char *str, char c);
char			**env_cpy(t_data *data, t_list_env *env);
int				del_one(t_env **env);
int				find_var_rap(t_list_env *env, t_env *new_node);

// signals
int				hook_signals(void);

// utils
void			print_env_arr(char **env);
void			pipes(t_data *data, int psize, t_spl_pipe *tmp);
void			do_cmd(t_data *data, t_spl_pipe *tmp);
int				put_exit_s(t_data *data, int status);
void			print_forme(t_env *head);
char			*clean_unprintable(char *arr);
char			*set_mode_quotes(char *s);
int				free_all(t_data *data);
#endif
