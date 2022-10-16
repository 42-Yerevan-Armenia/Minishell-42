#include "../includes/minishell.h"

char    *get_cmd(char   **paths, char *cmd)
{
    char    *tmp;
    char    *command;

    while (*paths)
    {
        tmp = ft_strjoin(*paths, "/");
        command = ft_strjoin(tmp, cmd);
        //free(tmp);
        if (access(command, F_OK) == 0)
            return (command);
        free(command);
        paths++;
    }
    return (NULL);
}

void    find_path(t_data *data)
{
    t_spl_pipe *tmp;

    data->path = getenv("PATH");
    tmp = data->cmd_line->head;
    while (tmp)
    {
        data->cmd_paths = ft_split(data->path, ':');
        // spl_pipe.pid = fork();
        if (tmp->pid < 0)
            printf("❌ Error");
        if (tmp->pid == 0)
        {
        	data->path = get_cmd(data->cmd_paths, *tmp->cmd);
            execve(data->path, tmp->cmd, &tmp->cmd[0]);
            // exit(0);
        }
        tmp = tmp->next;
    }
}

// int main(int ac, char **av, char **envp)
// {
// 	t_parse parser;
// 	t_data	data;
// 	int i = 0;
// 	int j = 0;

// 	i = 0;
// 	if (ac == 1)
// 	{
// 		init(&parser, &data, envp);
// 		data.error_message = NULL;
// 		// print_env(data.env->head);
// 		while (1)
// 		{
// 			parser.rd_ln = readline("minishell> ");
// 				// printf("barev\n");

// 			if (parser.rd_ln[0])
// 			{
// 				// printf("barev\n");
// 				parsing(&parser);

// 				// printf("❌ Error");
// 				find_path(&data);
// 				free_spl_pipe(&data.cmd_line);
// 			}
// 			free(parser.rd_ln);
// 		}
// 		free_envp(&data.env);
// 	}
// }
