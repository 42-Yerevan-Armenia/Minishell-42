#ifndef STRUCT_H
# define STRUCT_H

 #define METACHAR "|&;()<> \n\t"



typedef struct s_node
{
	char			**cmd;
	char			*dlm;
	struct s_node	*next;
	struct s_node	*prev;

}               t_node;

typedef struct s_list
{
	t_node   *head;
	t_node   *tail;
	// t_node   *node;
}               t_list;

typedef struct s_data
{
	t_list		*cmd_line;
	pid_t		pid;
	int			in;
	int			out;
	char		*cmd1;
	char		**cmd_args;
	char		**cmd_paths;
}               t_data;

typedef struct s_parse
{
	char		**spl_qutoes;
	char		**spl_pipe;
	t_data		*data;
	char		*rd_ln;
}               t_parse;
// typedef struct s_syntax
// {
	
// }               t_syntax;
#endif