/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:05:58 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/24 16:32:35 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define METACHARS "|&;()<> \n\t"
# define UNEXPECTED "|&;()"
# define UNEXPECTED_RED "|&;()><"
# define HANDLE	"<>"
# define QUOTES	"\"'`"
# define SPACES " \n\t\v\f\r"

# define APPEND_FILES 1
# define IN_FILES 2
# define OUT_FILES 3
# define HEREDOC 4
# define COMAND 5

# define EXPORT 2
# define ENV 1
# define FORME 4

# define HDOC_SQ_MODE 1
# define HDOC_DQ_MODE 0

# define TC_ON 50
# define TC_OFF 51

# define FREE_ON 7
# define FREE_OFF 8
# define FREE_1 1
# define FREE_2 2
# define UNPRINTABLE 1

# define SIGNAL 1
# define ENDF -1
# define START_RD_LN 100

# define L_MIN "9223372036854775808"
# define L_MAX "9223372036854775807"

extern int	g_sig;

//Pipes
# define FORK "🔻minishell> fork: Resource temporarily unavailable ❌\n"
# define INPUT_FILE "🔻minishell> Input File: No such file or directory ❌\n"
# define FAR ": filename argument required ❌\n"
# define USAGE ": usage: . filename [arguments]\n"
# define IS_DIR ": is a directory ❌\n"
# define NO_DIR ": No such file or directory ❌\n"
# define NO_PERM ": Permission denied ❌\n"
# define NOT_FOUND ": command not found ❌\n"

//Builtins
# define EXIT_ARG "🔻minishell> : exit: too many arguments ❌\n"
# define UNEXPECTED_TOKEN "🔻minishell: syntax error near unexpected token "
# define SHELL_INIT "shell-init: error retrieving current directory: getcwd:\
 cannot access parent directories: No such file or directory ❌\n"
# define BAD_RDR "🔻minishell: ambigous redirect\n"
# define CD_ERROR "🔻minishell: cd: error retrieving current directory: getcwd: cannot access parent\
 directories: No such file or directory ❌\n"
# define MAX_HDOC "minishell: maximum here-document count exceeded❌\n"

void	not_found(t_spl_pipe *tmp, t_data *data);
void	is_dir(t_spl_pipe *tmp, t_data *data);
void	no_dir(t_spl_pipe *tmp, t_data *data);
void	no_perm(t_spl_pipe *tmp, t_data *data);

#endif
