// #include "../includes/minishell.h"

// #include <stdio.h>
// #include <string.h>
// #include <sys/wait.h>
// #include <unistd.h>
// #include <stdarg.h>
// #include <errno.h>
// #include <stdlib.h>

// typedef int pipefd[2];

// static char *cmd0[] = { "who",                0 };
// static char *cmd1[] = { "awk",  "{print $1}", 0 };
// static char *cmd2[] = { "sort",               0 };
// static char *cmd3[] = { "uniq", "-c",         0 };
// static char *cmd4[] = { "sort", "-n",         0 };

// static char **cmds[] = { cmd0, cmd1, cmd2, cmd3, cmd4 };
// static int   ncmds = sizeof(cmds) / sizeof(cmds[0]);

// static const char *arg0 = "<undefined>";

// static void exec_pipe_command(int ncmds, char ***cmds, pipefd output);

// char    *get_cmd(char   **paths, char *cmd)
// {
//     char    *tmp;
//     char    *command;

//     while (*paths)
//     {
//         tmp = ft_strjoin(*paths, "/");
//         command = ft_strjoin(tmp, cmd);
//         //free(tmp);
//         if (access(command, F_OK) == 0)
//             return (command);
//         free(command);
//         paths++;
//     }
//     return (NULL);
// }

// // static void err_vsyswarn(char const *fmt, va_list args)
// // {
// //     int errnum = errno;
// //     fprintf(stderr, "%s:%d: ", arg0, (int)getpid());
// //     vfprintf(stderr, fmt, args);
// //     if (errnum != 0)
// //         fprintf(stderr, " (%d: %s)", errnum, strerror(errnum));
// //     putc('\n', stderr);
// // }

// // static void err_sysexit(char const *fmt, ...)
// // {
// //     va_list args;
// //     va_start(args, fmt);
// //     err_vsyswarn(fmt, args);
// //     va_end(args);
// //     exit(1);
// // }

// // /* With the standard output plumbing sorted, execute Nth command */
// // static void exec_nth_command(int ncmds, char ***cmds)
// // {
// //     //assert(ncmds >= 1);
// //     if (ncmds > 1)
// //     {
// //         pid_t pid;
// //         pipefd input;
// //         if (pipe(input) != 0)
// //             err_sysexit("Failed to create pipe");
// //         if ((pid = fork()) < 0)
// //             err_sysexit("Failed to fork");
// //         if (pid == 0)
// //         {
// //             /* Child */
// //             exec_pipe_command(ncmds-1, cmds, input);
// //         }
// //         /* Fix standard input to read end of pipe */
// //         dup2(input[0], 0);
// //         close(input[0]);
// //         close(input[1]);
// //     }
// //     execvp(cmds[ncmds-1][0], cmds[ncmds-1]);
// //     err_sysexit("Failed to exec %s", cmds[ncmds-1][0]);
// //     /*NOTREACHED*/
// // }

// /* Given pipe, plumb it to standard output, then execute Nth command */
// // static void exec_pipe_command(int ncmds, char ***cmds, pipefd output)
// // {
// //     //assert(ncmds >= 1);
// //     /* Fix stdout to write end of pipe */
// //     dup2(output[1], 1);
// //     close(output[0]);
// //     close(output[1]);
// //     exec_nth_command(ncmds, cmds);
// // }

// // static void err_syswarn(char const *fmt, ...)
// // {
// //     va_list args;
// //     va_start(args, fmt);
// //     err_vsyswarn(fmt, args);
// //     va_end(args);
// // }

// // static void exec_pipeline(int ncmds, char ***cmds)
// // {
// //     pid_t pid;
// //     if ((pid = fork()) < 0)
// //         err_syswarn("Failed to fork");
// //     if (pid != 0)
// //         return;
// //     exec_nth_command(ncmds, cmds);
// // }

// void    find_path(t_data *data)
// {
//     t_spl_pipe *tmp;
//     int  		res;

//     data->path = getenv("PATH");
//     tmp = data->cmd_line->head;
//     data->cmd_paths = ft_split(data->path, ':');
//     while (tmp)
//     {
//     	// readline("");
//         if ((tmp->pid = fork()) < 0)
//             printf("❌ Error");
//         // if (tmp->pid != 0)
//         // 	return;
//         if (tmp->pid == 0)
//         {
//         	data->path = get_cmd(data->cmd_paths, *tmp->cmd);
//             // printf("%s\n", data->path);
//             execve(data->path, tmp->cmd, &tmp->cmd[0]);
//         }
//         tmp = tmp->next;
//     }
//     tmp = data->cmd_line->head;
//     while (tmp)
//     {
//     	waitpid(tmp->pid, &res, 0);
//     	tmp = tmp->next;
//     }
//     data->exit_status = WEXITSTATUS(res);
//     // printf("data->exit_status = %d\n", data->exit_status);
// }

// // static void exec_arguments(int ac, char **av)
// // {
// //     /* Split the command line into sequences of arguments */
// //     /* Break at pipe symbols as arguments on their own */
// //     char **cmdv[ac/2];            // Way too many
// //     char  *args[ac+1];
// //     int cmdn = 0;
// //     int argn = 0;

// //     cmdv[cmdn++] = &args[argn];
// //     for (int i = 1; i < ac; i++)
// //     {
// //         char *arg = av[i];
// //         if (strcmp(arg, "|") == 0)
// //         {
// //             if (i == 1)
// //                 err_sysexit("Syntax error: pipe before any command");
// //             if (args[argn-1] == 0)
// //                 err_sysexit("Syntax error: two pipes with no command between");
// //             arg = 0;
// //         }
// //         args[argn++] = arg;
// //         if (arg == 0)
// //             cmdv[cmdn++] = &args[argn];
// //     }
// //     if (args[argn-1] == 0)
// //         err_sysexit("Syntax error: pipe with no command following");
// //     args[argn] = 0;
// //     exec_pipeline(cmdn, cmdv);
// // }

// // int main(int ac, char **av, char **envp)
// // {
// // 	t_parse parser;
// // 	t_data	data;
// // 	int i = 0;
// // 	int j = 0;

// // 	i = 0;
// // 	if (ac == 1)
// // 	{
// // 		init(&parser, &data, envp);
// // 		data.error_message = NULL;
// // 		// print_env(data.env->head);
// // 		while (1)
// // 		{
// // 			parser.rd_ln = readline("🔻minishell> ");
// // 			if (parser.rd_ln[0])
// // 			{
// // 				add_history(parser.rd_ln);
// // 				parsing(&parser);
// // 				// if (parser.data->cmd_line->head->heredoc[0])
// // 					parser.data->cmd_line->head->hdoc_input = ft_heredoc(&parser, parser.data->cmd_line->head->heredoc[i]);
// // 				// i = 0;
// // 				//find_path(&data);
// // 				if (ac == 1)
// // 					exec_pipeline(ncmds, cmds);
// // 				else
// // 					exec_arguments(&data);
// // 				free_spl_pipe(&data.cmd_line);
// // 				// printf(" 1 = %p\n", parser.data->cmd_line->head->hdoc_input);
// // 			}
// // 			free_arr(&parser.rd_ln);
// // 		}
// // 		free_envp(&data.env);
// // 	}
// // }
