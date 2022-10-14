#include "../includes/minishell.h"

char    *get_cmd(char **paths, char *cmd)
{
    char    *tmp;
    char    *command;

    while (*paths)
    {
        tmp = ft_strjoin(*paths, "/");
        command = ft_strjoin(tmp, cmd);
        if (access(command, F_OK & X_OK) == 0)
            return (command);
        free(command);
        paths++;
    }
    return (NULL);
}

void find_path(t_data data, t_parse parser)
{
    t_node  *node;
    int		pids;
    int		fd;

    *node->cmd = getenv("PATH");
    while (data.cmd_line->head)
    {
        data.cmd_paths = ft_split(*node->cmd, ':');
        //pipe(pipefd);
        node->pid = fork();
        if (node->pid < 0)
            printf("❌ Error\n");
        if (node->pid == 0)
        {
            data.cmd_args = ft_split(*data.cmd_line->head->cmd, ' ');
            data.cmd1 = get_cmd(data.cmd_paths, data.cmd_args[0]);
            execve(data.cmd1, data.cmd_args, node->cmd);
            exit(0);
        }
        data.cmd_line->head = data.cmd_line->head->next;
    }
}

int main(int ac, char **av)
{
	t_parse parser;
	t_data	data;

	if (ac == 1)
	{
		//signal(SIGINT, signal_callback_handler);
		//signal(SIGQUIT, signal_callback_handler);
		init(&parser, &data);
		data.error_message = NULL;
		parser.rd_ln = readline("minishell> ");
		parsing(&parser);
		find_path(data, parser);
	}
}

/*
Checks if the first word in the input is one of the builtin commands, if it
is, it executes it and returns -1, 0, or 1

int check_builtin(char **cmd)
{
	if (ft_(cmd, "echo"))
		return ();
	else if (ft_(cmd, "exit"))
		return ();
	else if (ft_(cmd, "export"))
		return ();
	else if (ft_(cmd, "cd"))
		return ();
	else if (ft_(cmd, "pwd"))
		return ();
	else if (ft_(cmd, "unset"))
		return ();
	else if (ft_(cmd, "env"))
		return ();
	return (0);
}
*/
