/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:33:40 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/27 12:44:12 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *find_path(char **env)
{
  //  printf("%s\n", *env);
    while (ft_strncmp("PATH", *env, 4))
        *env+=1;
    printf("%s\n", *env);
    return (*env + 5);//ignor PATH=
}

char    *get_cmd(char   **paths, char *cmd)
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

void    cmd_child(t_data data, char **av, char **envp)
{
    if (dup2(data.in, 0) == -1)
        printf("❌ DUP2");
     data.cmd_args = ft_split(av[2], ' ');
    data.cmd1 = get_cmd(data.cmd_paths, data.cmd_args[0]);
    execve(data.cmd1, data.cmd_args, envp);
    printf("execven chexav\n");
    exit (0);
}

int main(int ac, char **env)
{
    t_data data;
    add_node(data.cmd_line, "ls");
   // char    **env;
printf("%d\n", __LINE__);
    data.cmd_line = create_list();
    printf("%d\n", __LINE__);
    data.cmd_paths = ft_split(find_path(env), ':');
    printf("%d\n", __LINE__);
    data.pid = fork();
    if (data.pid < 0)
        printf("❌ Error");
    if (data.pid == 0)
        cmd_child(data, env, env);
    printf("%s\n", data.cmd_line->head->cmd);
    // dis_prompt();
    // readline("minishell");
}

void add_node(t_list *list, char *cmd)
{
    t_node  *new_node;
    t_node  *tmp;

    new_node = malloc(sizeof(t_list));
    new_node->cmd = cmd;
    new_node->next = NULL;
    if (list->head == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else 
    {
        tmp = list->head;
        while (tmp->next)
            tmp = tmp->next;
       tmp->next = new_node;
    }
}

t_list *create_list(void)
{
    t_list  *list;

    list = malloc(sizeof(t_list));
    list->head = NULL;
    list->tail = NULL;
    list->node = NULL;
    return (list);
}