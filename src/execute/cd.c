#include "../includes/minishell.h"

/* One way to create a pipeline of N processes */
//#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>

typedef int pipefd[2];

/* exec_nth_command() and exec_pipe_command() are mutually recursive */
static void exec_pipe_command(int ncmds, char ***cmds, pipefd output);

static const char *arg0 = "<undefined>";

static void err_setarg0(const char *av0)
{
    arg0 = av0;
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
    //assert(ncmds >= 1);
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
    //assert(ncmds >= 1);
    /* Fix stdout to write end of pipe */
    dup2(output[1], 1);
    close(output[0]);
    close(output[1]);
    exec_nth_command(ncmds, cmds);
}

/* Execute the N commands in the pipeline */
static void exec_pipeline(int ncmds, char ***cmds)
{
    //assert(ncmds >= 1);
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

/*  who | awk '{print $1}' | sort | uniq -c | sort -n */
static char *cmd0[] = { "who",                0 };
static char *cmd1[] = { "awk",  "{print $1}", 0 };
static char *cmd2[] = { "sort",               0 };
static char *cmd3[] = { "uniq", "-c",         0 };
static char *cmd4[] = { "sort", "-n",         0 };

static char **cmds[] = { cmd0, cmd1, cmd2, cmd3, cmd4 };
static int   ncmds = sizeof(cmds) / sizeof(cmds[0]);

static void exec_arguments(int ac, char **av)
{
    /* Split the command line into sequences of arguments */
    /* Break at pipe symbols as arguments on their own */
    char **cmdv[ac/2];            // Way too many
    char  *args[ac+1];
    int cmdn = 0;
    int argn = 0;

    cmdv[cmdn++] = &args[argn];
    for (int i = 1; i < ac; i++)
    {
        char *arg = av[i];
        if (strcmp(arg, "|") == 0)
        {
            if (i == 1)
                err_sysexit("Syntax error: pipe before any command");
            if (args[argn-1] == 0)
                err_sysexit("Syntax error: two pipes with no command between");
            arg = 0;
        }
        args[argn++] = arg;
        if (arg == 0)
            cmdv[cmdn++] = &args[argn];
    }
    if (args[argn-1] == 0)
        err_sysexit("Syntax error: pipe with no command following");
    args[argn] = 0;
    exec_pipeline(cmdn, cmdv);
}

int pipex(int ac, char **av)
{
    err_setarg0(av[0]);
    if (ac == 1)
    {
        /* Run the built in pipe-line */
        exec_pipeline(ncmds, cmds); 
    }
    else
    {
        /* Run command line specified by user */
        exec_arguments(ac, av);
    }
    //corpse_collector();
    return (0);
}

// int	ft_putstr(char *str)
// {
// 	while (str && *str)
// 		write(1, str++, 1);
// 	return (0);
// }

// static int	mod_env(char **str, char *value)
// {
//   int		i;
//   int		j;
//   char		*new_str;

//   j = 0;
//   i = 0;
//   while (*str && str[0][i] != '=')
//     i += 1;
//   i += 1;
//   if ((new_str = (char*)malloc(ft_strlen(value) + i + 3)) == NULL)
//     return (-1);
//   i = 0;
//   while (*str && str[0][i - 1] != '=')
//     new_str[j++] = str[0][i++];
//   i = 0;
//   while (value[i])
//     new_str[j + i] = value[i++];
//   new_str[j + i] = 0;
//   *str = new_str;
//   return (0);
// }

// static char	**cp_env(char **env)
// {
//   char		**new_env;
//   int		i;

//   i = 0;
//   while (env[i])
//     i = i + 1;
//   if ((new_env = (char**)malloc(sizeof(char*) * i + 2)) == NULL)
//     return (NULL);
//   new_env = env;
//   return (new_env);
// }

// static int	push_env(char ***env, char *variable, char *value)
// {
//   char		**new_env;
//   char		*new_var;
//   int		i;
//   int		j;

//   i = 0;
//   j = 0;
//   if ((new_env = cp_env(*env)) == NULL)
//     return (-1);
//   if ((new_var = (char*)malloc(ft_strlen(value) + ft_strlen(variable) + 2))
//       == NULL)
//     return (-1);
//   while (variable[i])
//     new_var[i] = variable[i++];
//   while (value[j])
//     new_var[j + i] = value[j++];
//   new_var[j + i] = 0;
//   i = 0;
//   while (new_env[i])
//     i = i + 1;
//   new_env[i++] = new_var;
//   new_env[i] = NULL;
//   return (0);
// }

// char	*add_egale(char *var)
// {
//   int	size;
//   char	*new_var;
//   int	i;

//   size = ft_strlen(var);
//   if ((new_var = (char*)malloc(size + 2)) == NULL)
//     return (NULL);
//   i = 0;
//   while (var[i])
//   {
//     new_var[i] = var[i];
//     i = i + 1;
//   }
//   new_var[i++] = '=';
//   new_var[i] = 0;
//   return (new_var);
// }

// int	my_setenv(char ***env, char *variable, char *value)
// {
//   char	**tmp_var;
//   int	i;

//   i = 0;
//   tmp_var = *env;
//   if (variable == NULL || value == NULL)
//     return (ft_putstr("usage: setenv VARIABLE VALUE\n"));
//   if (variable == NULL || ft_strlen(variable) == 0
//       || ft_strchr(variable, '=') != NULL)
//     return (ft_putstr("error : variable NULL or '=' in name\n"));
//   if ((variable = add_egale(variable)) == NULL)
//     return (-1);
//   while (tmp_var && tmp_var[i]
// 	 && ft_strncmp(variable, tmp_var[i], ft_strlen(variable)) != 0)
//     i = i + 1;
//   if (tmp_var == NULL || tmp_var[i] == NULL)
//   {
//     if ((push_env(env, variable, value)) == -1)
//       return (-1);
//   }
//   else if ((mod_env(&tmp_var[i], value)) == -1)
//     return (-1);
//   return (0);
// }

// int	cd_error(char ***tab_env)
// {
//   char	*str;
//   char	*pwd;
//   int	size;

//   size = 200;
//   if (tab_env == NULL)
//     return (-1);
//   if ((str = malloc(sizeof(char) * (size + 1))) == NULL)
//     return (-1);
//   if ((pwd = getcwd(str, size)) != NULL)
//     my_setenv(tab_env, "OLDPWD", pwd);
//   return (0);
// }


// int	main(int ac, char **tab)
// {
// if (ac > 1)
// {
//   if (tab[1] != NULL)
//     {
//       if (access(tab[1], R_OK) == -1 && tab[2] == NULL)
// 	{
// 	  perror(tab[1]);
// 	  return (0);
// 	}
//       else if (access(tab[1], F_OK) == -1 && tab[2] == NULL)
// 	{
// 	  perror(tab[1]);
// 	  return (0);
// 	}
//       else if (chdir(tab[1]) == -1 && tab[2] == NULL)
// 	{
// 	  perror(tab[1]);
// 	  return (0);
// 	}
//       else if (tab[2] != NULL)
// 	{
// 	  write(2, "cd: Too many arguments.\n", 24);
// 	  return (0);
// 	}
//       return (1);
//     }
//    }
//   return (0);
// }
