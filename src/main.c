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
        if (access(command, F_OK) == 0)
            return (command);
        free(command);
        paths++;
    }
    return (NULL);
}

void find_path(t_data data, char **av)
{
    while (ft_strncmp("PATH", *av, 4))
        *av += 1;
    *av += 5;
    while (data.cmd_line->head)
    {
        data.cmd_paths = ft_split(*av, ':');
        data.pid = fork();
        if (data.pid < 0)
            printf("❌ Error");
        if (data.pid == 0)
        {
            data.cmd_args = ft_split(data.cmd_line->head->cmd, ' ');
            data.cmd1 = get_cmd(data.cmd_paths, data.cmd_args[0]);
            if (!data.cmd1)
            {
                int i = 0;
                while (data.cmd_args[i])
                    free(data.cmd_args[i++]);
                free(data.cmd_args);
                free(data.cmd1);
            }
            execve(data.cmd1, data.cmd_args, av);
            exit(0);
        }
        else
            waitpid(data.pid, NULL, 0);
        data.cmd_line->head = data.cmd_line->head->next;
    }
}

int		env_len(char **env)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (env[++i])
		count++;
	return (count);
}

void			init_env(char **env)
{
	int		i;

	g_env = (char **)ft_malloc(sizeof(char *) * (env_len(env) + 1));
	i = -1;
	while (env[++i])
	{
		if (!(g_env[i] = ft_strdup(env[i])))
			exit(1) ;
	}
}

void	get_input(char **input)
{
	*input = ft_strnew(1);
}

int main(int ac, char **av, char **env)
{
    t_data data;
	char *input;
	char **cmd;
	
	init_env(env);
	while (1)
	{
	    data.cmd_line = create_list();
		get_input(&input);
		cmd = ft_split(*av, ';');
    	add_node(data.cmd_line, "echo Hello");
    	//add_node(data.cmd_line, "|");
    	//add_node(data.cmd_line, "wc Makefile");
    	find_path(data, av);
    	echo_builtin(cmd);
    	//printf("%d\n", __LINE__);
	}
	return (0);
}


