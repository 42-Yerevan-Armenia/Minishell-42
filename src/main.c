/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:33:40 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/03 15:22:32 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *get_cmd(char **paths, char *cmd)
{
    char    *tmp;
    char    *command;

    while (*paths)
    {
        tmp = ft_strjoin(*paths, "/");
        command = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(command, F_OK & X_OK) == 0)
            return (command);
        free(command);
        paths++;
    }
    return (NULL);
}

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void find_path(t_data data, char **av)
{
    *av = getenv("PATH");

    int pipefd[2];

    while (data.cmd_line->head)
    {
        data.cmd_paths = ft_split(*av, ':');
        open((char *)0, O_RDONLY);
	    open((char *)1, O_RDWR);
        pipe(pipefd);
        data.pid = fork();
        if (data.pid < 0)
            printf("❌ Error");
        if (data.pid == 0)
        {
            ft_close(pipefd[1]);
            dup2(pipefd[0], 0);
            data.cmd_args = ft_split(data.cmd_line->head->cmd, ' ');
            data.cmd1 = get_cmd(data.cmd_paths, data.cmd_args[0]);
            execve(data.cmd1, data.cmd_args, av);
            exit(0);
        }
        else
        {
            ft_close(pipefd[0]);
            dup2(pipefd[1], 1);
        }
        data.cmd_line->head = data.cmd_line->head->next;
    }
}

int main(int ac, char **av, char **env)
{
    t_data data;
	
    data.cmd_line = create_list();
    add_node(data.cmd_line, "echo Hello");
    //add_node(data.cmd_line, "|");
   	add_node(data.cmd_line, "ls | cat Makefile");
   	find_path(data, av);
   	//printf("%d\n", __LINE__);
	return (0);
}
