/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:05:58 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/07 17:56:36 by vaghazar         ###   ########.fr       */
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
# define START_RD_LN -1
# define TC_ON 50
# define TC_OFF 51
# define FREE_ON 7
# define FREE_OFF 8

extern int g_sig;

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
# define BUILTINS "1cd1echo1env1exit1export1pwd1unset"
# define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token "
# define SHELL_INIT "shell-init: error retrieving current directory: getcwd:\
 cannot access parent directories: No such file or directory"
# define BAD_RDR "minishell: ambigous redirect"
# define NO_SUCH_F ": No such file or directory ❌\n"
# define CD_ERROR "minishell: cd: error retrieving current directory: getcwd: cannot access parent\
 directories: No such file or directory ❌\n"

#endif
