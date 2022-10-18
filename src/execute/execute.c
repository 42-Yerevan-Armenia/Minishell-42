#include "../includes/minishell.h"

/*char    *get_cmd(char   **paths, char *cmd)
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
        }
        tmp = tmp->next;
    }
}*/

void pipex(t_data *data);

void    dis_prompt();
int     split_quotes(t_parse *parser);
int     split_pipe(t_parse *parser);
int     pipe_join(t_parse *parser);
void    find_path(t_data *data);
int parsing(t_parse *parser);
int	init(t_parse *parser, t_data *data, char **envp);

/* One way to create a pipeline of N processes */

#include <assert.h>
#include <string.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <errno.h>

typedef int pipefd[2];

/* exec_nth_command() and exec_pipe_command() are mutually recursive */
static void exec_pipe_command(int ncmds, char ***cmds, pipefd output);

static const char *arg0 = "<undefined>";

static void err_setarg0(const char *argv0)
{
    arg0 = argv0;
}

static void err_vsyswarn(char const *fmt, va_list args)
{
    int errnum = errno;
    fprintf(stderr, "%s:%d: ", arg0, (int)getpid());
    vfprintf(stderr, fmt, args);
    if (errnum != 0)
        fprintf(stderr, " (%d: %s)", errnum, strerror(errnum));
    putc('\n', stderr);
}

static void err_syswarn(char const *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    err_vsyswarn(fmt, args);
    va_end(args);
}

static void err_sysexit(char const *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    err_vsyswarn(fmt, args);
    va_end(args);
    exit(1);
}

/* With the standard output plumbing sorted, execute Nth command */
static void exec_nth_command(int ncmds, char ***cmds)
{
    assert(ncmds >= 1);
    if (ncmds > 1)
    {
        pid_t pid;
        pipefd input;
        if (pipe(input) != 0)
            err_sysexit("Failed to create pipe");
        if ((pid = fork()) < 0)
            err_sysexit("Failed to fork");
        if (pid == 0)
        {
            /* Child */
            exec_pipe_command(ncmds-1, cmds, input);
        }
        /* Fix standard input to read end of pipe */
        dup2(input[0], 0);
        close(input[0]);
        close(input[1]);
    }
    execvp(cmds[ncmds-1][0], cmds[ncmds-1]);
    err_sysexit("Failed to exec %s", cmds[ncmds-1][0]);
    /*NOTREACHED*/
}

/* Given pipe, plumb it to standard output, then execute Nth command */
static void exec_pipe_command(int ncmds, char ***cmds, pipefd output)
{
    assert(ncmds >= 1);
    /* Fix stdout to write end of pipe */
    dup2(output[1], 1);
    close(output[0]);
    close(output[1]);
    exec_nth_command(ncmds, cmds);
}

/* Execute the N commands in the pipeline */
static void exec_pipeline(int ncmds, char ***cmds)
{
    assert(ncmds >= 1);
    pid_t pid;
    if ((pid = fork()) < 0)
        err_syswarn("Failed to fork");
    if (pid != 0)
        return;
    exec_nth_command(ncmds, cmds);
}

/* Collect dead children until there are none left */
static void corpse_collector(void)
{
    pid_t parent = getpid();
    pid_t corpse;
    int   status;
    while ((corpse = waitpid(0, &status, 0)) != -1)
    {
        fprintf(stderr, "%d: child %d status 0x%.4X\n",
                (int)parent, (int)corpse, status);
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
