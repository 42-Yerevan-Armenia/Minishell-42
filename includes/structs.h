#ifndef STRUCT_H
# define STRUCT_H

 #define METACHARS "|&;()<> \n\t"
 #define HANDLE	"<>"
 #define SPACES " \n\t\v\f\r"
 #define APPEND_FILES 1
 #define IN_FILES 2
 #define OUT_FILES 3
 #define HEREDOC 4
 #define COMAND 5




typedef struct s_spl_pipe
{
	int				is_args;
	int				fd_in;
	int				fd_out;
	int				output_mode;
	int				input_mode;
	int				flag_new_pipe;
	pid_t			pid;
	char			**cmd;
	char			*dlm;
	char			**out_files;
	char			**in_files;
	char			**heredoc;
	char			*error_message;
	struct s_spl_pipe	*next;
	struct s_spl_pipe	*prev;
}               t_spl_pipe;

typedef struct s_list_spl_pipe
{
	t_spl_pipe   *head;
	t_spl_pipe   *tail;
}               t_list_spl_pipe;

typedef struct s_envp
{
	int		is_export;
	char	*key;
	char	*val;
	struct s_envp	*next;
	struct s_envp	*prev;
}               t_envp;

typedef struct s_list_envp
{
	t_envp   *head;
	t_envp   *tail;
}               t_list_envp;

typedef struct s_data
{
	char			*path;
	char			**cmd_paths;
	char			*error_message;
	t_list_spl_pipe	*cmd_line;
	t_list_envp		*env;
}               t_data;

typedef struct s_parse
{
	char		*key;
	char		*val;
	char		**spl_qutoes;
	char		**spl_pipe;
	char		**join_pipe;
	t_data		*data;
	char		*rd_ln;
}               t_parse;

typedef struct s_elem
{
	int	out_file;
	int	in_file;
	int	heredoc;
	int	out_append_files;
}               t_elem;


#endif