#ifndef DEFINES_H
# define DEFINES_H

 #define METACHARS "|&;()<> \n\t"
 #define UNEXPECTED "|&;()"
 #define HANDLE	"<>"
 #define QUOTES	"\"'`"
 #define SPACES " \n\t\v\f\r"
 #define APPEND_FILES 1
 #define IN_FILES 2
 #define OUT_FILES 3
 #define HEREDOC 4
 #define COMAND 5
 #define EXPORT 2
 #define ENV 1
 #define FORME 4
 #define HDOC_SQ_MODE 1
 #define HDOC_DQ_MODE 0
 #define START_RD_LN 100
 
//Pipes
 #define FORK "🔻minishell> fork: Resource temporarily unavailable ❌\n"
 #define INPUT_FILE "🔻minishell> Input File: No such file or directory ❌\n"
 #define NOT_FOUND "🔻minishell> %s: command not found ❌\n"

//Builtins

 #endif
