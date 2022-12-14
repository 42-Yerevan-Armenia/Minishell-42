/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:51:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/22 16:42:50 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_parse	t_parse;
typedef struct s_data	t_data;

typedef struct s_spl_pipe
{
	int					fd_in;
	int					fd_out;
	int					fd_hdc;
	int					input_mode;
	int					hdoc_mode;
	int					flag_new_pipe;
	int					tmp;
	long				pid;
	char				*f_name;
	char				**cmd;
	char				**heredoc;
	char				**rdc;
	t_data				*data;
	struct s_spl_pipe	*next;
	struct s_spl_pipe	*prev;
}						t_spl_pipe;

typedef struct s_list_spl_pipe
{
	int					size;
	t_spl_pipe			*head;
	t_spl_pipe			*tail;
}						t_list_spl_pipe;

typedef struct s_env
{
	int					is_export;
	char				*key;
	char				*val;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_list_env
{
	size_t				size;
	t_env				*head;
	t_env				*tail;
}						t_list_env;

typedef struct s_data
{
	int					psize;
	int					res;
	int					exit_status;
	int					fork_res;
	char				*path;
	char				**cmd_paths;
	char				**envp;
	char				**builtins;
	t_parse				*parser;
	t_list_spl_pipe		*cmd_line;
	t_list_env			*env;
	t_list_env			*env_exp;
}						t_data;

typedef struct s_parse
{
	int					l_arr;
	char				*rd_ln;
	char				*key;
	int					**hdoc_mode;
	char				**spl_qutoes;
	char				**spl_pipe;
	char				**join_pipe;
	char				**hered_res;
	t_data				*data;
}						t_parse;

typedef struct s_elem
{
	int					hdoc;
	int					out_a_f;
	int					rdc;
}						t_elem;

typedef struct s_vars
{
	int					i;
	int					j;
	int					k;
	int					c;
	int					t;
}						t_vars;

#endif
