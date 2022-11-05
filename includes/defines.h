/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:05:58 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/05 20:24:16 by vaghazar         ###   ########.fr       */
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

//Pipes
# define FORK "🔻minishell> fork: Resource temporarily unavailable ❌\n"
# define INPUT_FILE "🔻minishell> Input File: No such file or directory ❌\n"
# define IS_DIR "🔻minishell> %s: is a directory ❌\n"
# define NO_DIR "🔻minishell> %s: No such file or directory ❌\n"
# define NOT_FOUND "🔻minishell> %s: command not found ❌\n"

//Builtins
# define EXIT_ARG "🔻minishell> : exit: too many arguments ❌\n"
# define BUILTINS "cd echo env exit export pwd unset"
# define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token"
# define SHELL_INIT "shell-init: error retrieving current directory: getcwd:\
 cannot access parent directories: No such file or directory"
# define BAD_RDR "minishell: ambigous redirect"
# define NO_SUCH_F ": No such file or directory"

//Tokens
//  #define RED_INPUT		1	// <
//  #define RED_OUTPUT		2	// >
//  #define RED_OUT_APP	3	// >>
//  #define HERE_DOC		4	// <<
//  #define PIPE			5	// |
//  #define AND_OR			6	// &&
//  #define OR_IF			7	// ||
//  #define EXIT_STATUS	8	// &?
//  #define OPTION			9	// --\s -\s
//  #define WORD			10	// \s
//  #define FD				11	// \d
//  #define DELIMITER		12	// <<\s
//  #define L_BRACE		13	// (
//  #define R_BRACE		14	// )
//  #define FILE			15	// \s
//  #define CMD			16	// \s
//  #define ARGUMENT		17	// \s
//  #define NO_TOKEN		18	// n\a

#endif
