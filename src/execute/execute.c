#include "../includes/minishell.h"

char    *get_cmd(char   **paths, char *cmd)
{
    char    *tmp;
    char    *command;

    while (*paths)
    {
        tmp = ft_strjoin(*paths, "/");
        command = ft_strjoin(tmp, cmd);
        if (access(command, F_OK) == 0)
            return (command);
        free(command);
        paths++;
    }
    return (NULL);
}

void close_fds(int (*fds)[2], int psize)
{
    int i;
    int ret_fd;

    i = -1;
    while (++i < psize - 1)
    {
        ret_fd = close(fds[i][1]);
        ret_fd = close(fds[i][0]);
        if (ret_fd != 0 && !ft_perror("minishell:"))
            exit (1);
    }
}

void    open_pipes(int i, int (*fds)[2], int psize)
{
    if (i == 0)
    {
        if (dup2(fds[0][1], 1) < 0 && !ft_perror("minishell:"))
            exit(1);
    }
    else if (psize - 1 == i)
    {
        if (dup2(fds[i - 1][0], 0) < 0 && !ft_perror("minishell:"))
            exit(1);
    }
    else
    {
        dup2(fds[i - 1][0], 0);
        dup2(fds[i][1], 1);
    }
}

int    do_cmd(t_data *data, t_spl_pipe *tmp)
{
    data->path = get_cmd(data->cmd_paths, *tmp->cmd);
    if (!data->path && !free_arr(&data->path) && !ft_perror("minishell"))
        return (127);
    if (execve(data->path, tmp->cmd, &tmp->cmd[0]) == -1 && !ft_perror("minishell:"))
        exit(1);
    return (0);
}

int free_fds(int (*fds)[2])
{
    free(fds);
    return (0);
}

int    execute(t_data *data)
{
    t_spl_pipe *tmp;
    int         psize;
    int         res;
    int         (*fds)[2];
    int         i;

    tmp = data->cmd_line->head;
    psize = data->cmd_line->size;
    data->path = getenv("PATH");
    data->cmd_paths = ft_split(data->path, ':');
    fds = malloc(sizeof (*fds) * (psize - 1));
    if (!fds && !ft_perror("minishell:"))
        exit(1);
    i = -1;
    while (++i < psize - 1)
        if (pipe(fds[i]) == -1 && !ft_perror("minishell:"))
            return(1);
    i = 0;
    while (i < psize)
    {
            tmp->pid = fork();
            if (tmp->pid == -1 && !ft_perror("minishell:"))
                return(2);
            if (tmp->pid == 0)
            {
                if (psize == 1 && do_cmd(data, tmp) && !free_fds(fds))
                    return (3);
                else
                {
                    open_pipes(i, fds, psize);
                    close_fds(fds, psize);
                    do_cmd(data, tmp);
                }
            }
        tmp = tmp->next;
        i++;
    }
    close_fds(fds, psize);
    tmp = data->cmd_line->head;
    while (tmp)
    {
        waitpid(tmp->pid, &res, 0);
        tmp = tmp->next;
    }
    data->exit_status = WEXITSTATUS(res);
    return (0);
}

// int main(int ac, char **av, char **envp)
// {
//     t_parse parser;
//     t_data  data;
//     int i = 0;
//     int j = 0;

//     i = 0;
//     if (ac == 1)
//     {
//         init(&parser, &data, envp);
//         data.error_message = NULL;
//         // print_env(data.env->head);
//         while (1)
//         {
//             parser.rd_ln = readline("🔻minishell> ");
//             if (parser.rd_ln[0])
//             {
//                 add_history(parser.rd_ln);
//                 parsing(&parser);
//                 // if (parser.data->cmd_line->head->heredoc[0])
//                     parser.data->cmd_line->head->hdoc_input = ft_heredoc(&parser, parser.data->cmd_line->head->heredoc[i]);
//                 // i = 0;
//                 execute(&data);
//                 free_spl_pipe(&data.cmd_line);
//                 // printf(" 1 = %p\n", parser.data->cmd_line->head->hdoc_input);
//             }
//             free_arr(&parser.rd_ln);
//         }
//         free_envp(&data.env);
//     }
// }
