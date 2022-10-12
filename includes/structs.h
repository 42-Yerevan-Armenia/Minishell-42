#ifndef STRUCT_H
# define STRUCT_H

 #define METACHARS "|&;()<> \n\t"
 #define HANDLE	"<>"
 #define SPACES " \n\t"
 #define APPEND_FILES 1
 #define IN_FILES 2
 #define OUT_FILES 3
 #define HEARDOC 4




typedef struct s_node
{
	int				is_args;
	int				fd_in;
	int				fd_out;
	int				output_mode;
	char			**cmd;
	char			*dlm;
	char			**in_files;
	char			**out_files;
	char			**out_append_files;
	char			**heardocs;
	char			*error_message;
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
	int			in;
	int			out;
	pid_t		pid;
	char		*cmd1;
	char		**cmd_args;
	char		**cmd_paths;
	char		*error_message;
	t_list		*cmd_line;
}               t_data;

typedef struct s_parse
{
	char		**spl_qutoes;
	char		**spl_pipe;
	char		**join_pipe;
	t_data		*data;
	char		*rd_ln;
}               t_parse;
// typedef struct s_syntax
// {
	
// }               t_syntax;



typedef struct s_elem
{
	int	out_file;
	int	in_file;
	int	heardoc;
	int	out_append_files;
}               t_elem;


#endif