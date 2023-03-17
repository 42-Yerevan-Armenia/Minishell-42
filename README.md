# Minishell-42

## Table of Contents
1. [What is Minishell?](#p1)
    - [The subject](#p1.1)
    - [Understand the project](#p1.2)
2. [Before parsing](#p2)
3. [Parsing](#p3)
    - [Separations](#p3.1)
    - [Pipes](#p3.2)
    - [Command and Arguments](#p3.3)
    - [Protections](#p3.4)
    - [Redirections](#p3.5)
    - [Environment variables](#p3.6)
4. [Execution](#p4)
    - [Redirections in pipes](#p4.1)
    - [Pipes/signals/process links](#p4.2)
    - [Error managment](#p4.3)
5. [Builtins](#p5)
    - [Env, export, unsety](#p5.1)
    - [Exit](#p5.2)
    - [Cd, pwd, echo](#p5.3)
6. [References](#p6)
7. [Checklist](#cl)

## <a name="p1">What is Minishell?</a>

### <a name="p1.1">The subject</a>

  <a>
    <img src="https://d33wubrfki0l68.cloudfront.net/45825999a370278a2d392daafce3e7a95de0fff2/3bada/img/logo/svg/full_colored_light.svg" width="300" height="180">
  </a>

The goal of Minishell is to create a shell.

What is a shell? Basically an operating system with two elements:

**The kernel:** which performs the fundamental functions of the operating system such as the management of memory, processes, files...
**The shell:** the interface between the user and the kernel, which allows the user to communicate with the operating system through a command language. The user can enter commands in the terminal. **Thanks to the command line interpreter (such as bash or zsh which are shells), the commands entered are executed. --> We will create our own little shell.**

### <a name="p1.2">Understand the project</a>

Here is a short summary of what every variable is used for

| Parameter | Description |
| :-------: | :---------: |
| ``cmd_line`` | Linked list containing a ``t_list_spl_pipe`` node with all commands separated by pipes |
| ``cmd`` | Equivalent of the typical ``argv``, containing the command name and its parameters when needed |
| ``cmd_paths`` | If not a builtin, first available path for the executable denoted by ``argv[0]`` from the ``PATH`` variable |
| ``fd_in`` | Which file descriptor to read from when running a command (defaults to ``stdin``) |
| ``fd_out`` | Which file descriptor to write to when running a command (defaults to ``stdout``) |
| ``envp`` | Up-to-date array containing ``t_list_env`` node for the shell environment |
| ``pid`` | Process ID of the minishell instance |
| ``exit_status`` | Status of the most-recently-executed command |

## <a name="p2">Before parsing</a>

- Get all environment variables

When you type env in the terminal you see all the environment variables. As a main parameter, env is a char** which contains all these environment variables in the form: env[0] = TMPDIR=/var/folders/7g/g6ksr7hd0mjcyjwkj_mqdmgm0000gn/T/ . A value of 0 indicates the end of the array.

```
int	main(int ac, char **av, char **envp)
```

- Get PATH (which is in envp) in a char**

PATH = variable used by the operating system to locate command executable files. Like imagine when you do ``ls`` and PATH=/usr/local/bin:/usr/bin:/bin:, that means the system will look for an executable file called ls which corresponds to ``ls`` and it will look in ``/usr/local/bin`` if it doesn't find it, it will go to ``/usr/bin`` then to ``/bin`` So when the user will type commands that are not in our builtins we will need to know the paths of PATH.

```
ft_split(PATH, ':');
```

- Get the command line and write the prompt

`` 🔻minishell> `` this is the command prompt.

```
parser->rd_ln = readline("🔻minishell> ");
```

## <a name="p3">Parsing</a>

The parser is the part of the program responsible to read, understand and translate a command to a format the interpreter is able to work with. It is also responsible to check the validity of the input regarding a defined set of rules and to rise an error if the command is not valid.

- o easily understand linked lists: [video](https://www.youtube.com/watch?v=uBZHMkpsTfg&list=PLfqABt5AS4FmXeWuuNDS3XGENJO1VYGxl)

### <a name="p3.1">Separations</a>
Functions that create nodes:
```
t_list  *create_list(void)
{
  t_list  *list;

  list = malloc(sizeof(t_list));
  if (list == NULL && !ft_perror("🔻minishell: "))
    exit(1);
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return (list);
}
```
```
t_spl_pipe  *add_pipe(t_list_spl_pipe *list, t_spl_pipe *new_pipe)
{
  list->size++;
  if (list->head == NULL)
  {
    list->head = new_pipe;
    list->tail = new_pipe;
  }
  else
  {
    list->tail->next = new_pipe;
    new_pipe->prev = list->tail;
    list->tail = list->tail->next;
  }
  return (new_pipe);
}
```
Print nodes:
```
void print_info(t_parse *parser)
{
  int i = 0;
  t_spl_pipe *tmp = parser->data->cmd_line->head;

  while (tmp)
  {
    printf("\n----------------------------------\n");
    i = 0;
    printf("**CMD - ");
    while (tmp->cmd && tmp->cmd[i])
      printf("🛑 %s ", tmp->cmd[i++]);
    printf("\n\n*********************************\n");
    tmp = tmp->next;
  }
}
```

### <a name="p3.2">Pipes</a>
Example: ls -la | who


- ls is executed and its stdout is the who stdin, which is executed in turn ([Github pipex](https://github.com/42-Yerevan-Armenia/Pipex-42))
- who is executed

We parse list where each node contains cmd_line (parsed at the top). If cmd_line contains a pipe, a linked list data->cmd_line is created in the node in question. In data->cmd_line we make one node per command between pipes. From where :

- Check in each cmd_line of each node of t_list_spl_pipe *list if there are pipes
- If there is a split of '|' in a char **
- We enter this char** in a linked list (data->cmd_line->size) inside the node where cmd_line contains pipes
- Then we browse our list: If data->cmd_line->size == NULL, it means that there is no pipe, we can execute directly from which is in list->cmd_line. On the other hand if data->cmd_line->size != NULL, there are pipes so we will execute each data->cmd_line->head->cmd[0]. Before moving to the next node in list.

### <a name="p3.3">Command and Arguments</a>
Either the command is in our builtins or not in this second case, it will be necessary to make a system call with execve. => So we parsed into a direct char** (for both possibilities) ready to be sent to execve if needed.

Example: echo -n hello

- here echo is ours, but otherwise execve(file, argv)
- argv[0]: this is the command, echo
- argv[1]: the first argument, -n (this options can be pasted in a char* )
- arg[2]: the second argument, hello
- argv[3]: we always end with a NULL

To do :

- Create the char**
- Malloc the char** at each turn because we don't know in advance how many arguments
- As soon as there is a *space* that is not protected, we move on to the next argument
- Pay attention to the protections

**Warning: the end of an argument is a space which is not in quotes and which is not preceded by an escape character:**

### <a name="p3.4">Protections</a>

#### Quotes
|  | in simple quotes | in double quotes |
| :--: | :---------------------------: | :---------------------------: |
| ‘ | odd number of single quotes is not good, even if there is a \ (bash-3.2$ echo c'o\'u'cou) | single quotes in a double quote lose their meaning, so even if there is an odd number of single quotes it's ok, even if there is a \ (bash-3.2$ ec"ho" good"'j'o'u "r)(bash-3.2$ ec"ho" good"i where"r) |
| “ | double quotes in single quotes lose their meaning so even if there is an odd number of double quotes it's ok, even if there is a \ (bash-3.2$ echo co'c"o"u') (bash- 3.2$ echo co'"c\"o"u') | odd number of double quotes is not good (bash-3.2$ ec"ho" bon"jo"u"r). hello) |
| $ | does not retain its special environment meaning (bash-3.2$ '$PATH') | retains its special meaning of environment (bash-3.2$ “$PATH”) |
| / | does not retain its meaning (bash-3.2$ echo bo'njou\$r') | retains its meaning only when followed by ``"`` (bassh−3.2 echo bo"njo\$r") (bash-3.2$ ec"ho" bon"jo\"u"r) (bash-3.2$ echo "\\") |

So inside a double quote: ``$`` must call the environment variable

### <a name="p3.5">Redirects</a>
too well explained: [article]()

To capture stdin stdout stderr, I tell myself that each time I type a command, it receives an stdin, it runs, the result is printed on stdout and the error message is printed on stderr. Basically stdin is the keyboard, and stdout and stderr are direct in the terminal (the screen). But we can redirect to other sources other than the keyboard or the screen. For example, redirect standard output to a file. For this, the numbers of the flow descriptors are used.

- standard input (fd = 0)
- standard output (fd = 1)
- error output (fd = 2)

| Example | Description |
| :-------------: | :---------------------------: |
| ls > file_list.txt | create .txt and write output to file |
| ls >> file_list.txt | saved at the end of the file instead of overwriting it if it already exists |
| cat < notes.csv | Used to read data from a file and send it to a command. Here equivalent to writing “cat notes.csv” |

Exemple : cmd>A>B>C>D

- Create all files
```
sstderr = open(copy->redir.out2, O_CREAT | O_RDWR | 0644);
sstdin = open(copy->redir.in, O_RDONLY);
sstdout = open(copy->redir.out1, O_CREAT | O_RDWR | 0644);
```
- Save fd from last D file
- Do not put the >A>B>C>D in char** that we send to execve
- We will redirect the stdout to the last file D

| Redirection of output '>' | Redirection of input '<' |
| :-------------: | :---------------------------: |
| create the file if it does not exist | if file does not exist: no such file or directory |
| By default equivalent to 1> , By default overwrites the file in which we redirect, X> where X will take the value of the identifier of the descriptor (for example 1>ls vi) | < file |
| >> add at the end of the file so do not overwrite | << word allows to send a content to a command with the direct keyboard. Where typing “word” here allows you to stop (<<< and <<: it's a bonus I believe) |


### <a name="p3.6">Environment variables</a>
→ do not manage local variables

Principle

- Declaration: variable name=CONTENT
- Useage

| format | principe | exemple|
| :-------------: | :---------------------------: | :---------------------------: |
| variable or “$variable” or "${variable}" | replace the environment variable with its value | it can be everywhere in a redirect, in quotes: ls $HOME/Desktop , echo abc > $COLORTERM , echo coucou$COLORTERM |

## <a name="p4">Execution</a>
### <a name="p4.1">Redirections in pipes</a>
```
Redirection

dup2(tmp->fd_out, 1);
dup2(tmp->fd_in, 0);
close(tmp->fd_out);
close(tmp->fd_in);

int execution(int (*fds)[2], int psize, t_spl_pipe *head, t_data *data)
{
  int     i = -1;
  t_spl_pipe  *tmp = head;

  while (++i < psize - 1)
    if (pipe(fds[i]) == -1)
      close_fds(fds, i + 1);
  while (++i < psize)
  {
    tmp->pid = fork();
    if (tmp->pid == 0)
    {
      signal(SIGQUIT, SIG_DFL);
      redirection;
      execute cmds;
    }
    tmp = tmp->next;
  }
  return (0);
}

```
### <a name="p4.2">Pipes/signals/process links</a>

- Pipes/Processes with fork: [Github pipex](https://github.com/42-Yerevan-Armenia/Pipex-42)
- Signals: Attention, the ctrl-D does not work normally with something in the line: it is supposed to exit only on an empty line

### <a name="p4.3">Error managment</a>

## <a name="p5">Builtins</a>
| Builtin | Description | Options | Parameters | Helpful Functions |
| :-----: | :---------: | :-----: | :--------: | :---------------: |
| ``echo`` | Prints arguments separated with a space followed by a new line | ``-n`` | :heavy_check_mark: | [write](https://man7.org/linux/man-pages/man2/write.2.html) |
| ``cd`` | Changes current working directory, updating ``PWD`` and ``OLDPWD`` | :x: | :heavy_check_mark: | [chdir](https://man7.org/linux/man-pages/man2/chdir.2.html) |
|  ``pwd``| Prints current working directory | :x: | :x: | [getcwd](https://www.man7.org/linux/man-pages/man3/getcwd.3.html) |
| ``env`` | Prints environment | :x: | :x: | [write](https://man7.org/linux/man-pages/man2/write.2.html) |
| ``export`` | Adds/replaces variable in environment | :x: | :heavy_check_mark: | :x: |
| ``unset`` | Removes variable from environment | :x: | :heavy_check_mark: | :x: |
| ``exit`` | Process termination | :x: | :heavy_check_mark: | [exit](https://man7.org/linux/man-pages/man3/exit.3.html) |

### <a name="p5.1">Env, export, unsety</a>
#### env et export
|  | env | export | ./minishell |
| :-------------: | :-------------: | :-------------: | :-------------: |
| without argument | lists all environment variables in random order. in the form: name=value | list all environment variables in ascii order. in the form: declare -x name=”value” or declare -x name | creating a child process |
| without = (export test1) | test1 does not appear | declare -x test1 | test1 is not inherited >exit , test1 is still there with export |
| with a = (export test2=) (export test 3=hello) | test2= test3=coucou | declare -x test2="" declare -x test3="coucou" | test2 and test 3 are inherited >exit , test2 and test 3 are still there |
| multiple arguments (export test= o) | test= | declare -x o declare -x test="" | test is inherited, we are not inherited >exit , test is still there , where is still there with export |

unset
| unset name | remove environment variable name |
| :-------------: | :---------------------------------------: |
| unset *variable that does not exist* | Canceling a variable or function that has not been previously defined should not be considered an error and does not result in an abort. |
| unset test1 test2 | Can unset multiple variables at the same time |

### <a name="p5.2">Exit</a>
exit

- exit [n]
- causes the shell program to terminate with a return code ($?) equal to n.
- If n is not specified, the return code provided is that of the last command executed.
- exit only takes integer arguments between 0 and 255, hence:
```
atoi adapted to exit, which returns a long long (see tests below)
exit_status = ft_atoi(args[1]) % 256;
```
| Tests |
| :-------------: |
| exit ' 3' |
| exit -1 |
| exit -9223372036854775808 |
| exit 9223372036854775807 |
| exit +3  |
| exit 2000000 |
| exit -2147483649 |

| example | error |
| :-------------: | :-------------: |
| exit 0 bonjour | bash: exit: too many arguments |
| exit coucou | exit: coucou: numeric argument required |

warning: exit does not run with these errors

**$?**
- All Linux commands return an error code between 0 and 255.
- The value 0 represents the value true (command success).
- Values greater than 0 represent false (command failure).
- The error code of the last command used is contained in the variable $?


| **$?** | description |
| :-----: | :-------------: |
| 1 | standard for general errors, such as a division by zero |
| 2 | improper use of built-in commands, per Bash documentation |
| 126 | the command called cannot be executed, rights problem or command not executable |
| 127 | command not found, possible problem with $PATH or typing error |
| 128 | invalid command argument |
| 128+n | 128 + signal number |
| 130 | finished with Ctrl-C (130 = 128 + 2) |
| 255 | exit code out of bounds eg exit -1 |
| 258 | syntax error near unexpected token `\' |
Find out the error code of a call to a command / signal: waitpid(pid_t pid, int *status, int options);

- WIFEXITED(status) = returns true if the child terminated normally, ie by a call to exit(3) or exit(2), or by a return from main(). And in this case we can call: WEXITSTATUS(status) = returns the exit code of the child. This code consists of the low 8 bits of the status argument that the child supplied to exit(3) or _exit(2) or the argument of a return command in main(). "This macro can only be evaluated if WIFEXITED returned true".
- WIFSIGNALED(status) = returns true if the child terminated due to a signal. And in this case we can call: WTERMSIG(status) = returns the number of the signal which caused the end of the child. "This macro can only be evaluated if WIFSIGNALED returned true".

```
void  sig_wait(t_spl_pipe *tmp, t_data *data)
{
  while (tmp)
  {
    waitpid(tmp->pid, &data->res, 0);
    tmp = tmp->next;
  }
  if (data->fork_res == -1)
    return ;
  else if (WIFEXITED(data->res))
    data->exit_status = WEXITSTATUS(data->res);
  else if (WIFSIGNALED(data->res))
  {
    data->exit_status = WTERMSIG(data->res) + 128;
    if (WTERMSIG(data->res) == SIGQUIT)
      ft_putstr_fd("Quit: 3\n", 2, FREE_OFF);
    if (WTERMSIG(data->res) == SIGINT)
      write(1, "\n", 1);
  }
}
```

### <a name="p5.3">Cd, pwd, echo</a>



## <a name="p6">References</a>

- [42 Docs](https://harm-smits.github.io/42docs/projects/minishell)
- [ulimit](https://phoenixnap.com/kb/ulimit-linux-command)


## <a name="cl">Checklist</a>

| N | Compile | Flags |
| :-----: | :-------------: | :-------------: |
| 1 | Check usage of -Wall -Wextra -Werror | 💀 invalid compilation |
| 2 | minishell compile without errors | 💥  Crash |
| 3 | Makefile must not re-link | 💀 invalid compilation |

## Frome here
- if something crashes use ``💥 Crash`` flag 
- if something is not working use ``⚠️ incomplete work`` flag

| N | Simple command & global | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Execute a simple command with an absolute path | use commands in /bin directory |
| 1.1 | /bin/ls | /bin/echo |
| 2 | How many global variables? Why? | Explain to evaluators. |
| 3 | Test an empty command |  |
| 4 | Test only spaces or tabs |  |

| N | Arguments & history | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Execute a simple command with an absolute path with/without any quotes or double quotes | use commands in /bin directory |
| 1.1 | /bin/ls | /bin/echo |
| 2 | Repeat 1.1 multiple times with different commands and arguments | |

| N | echo | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Execute the ``echo`` command | with/without arguments or the -n option |
| 1.1 | echo a | echo 'a' |
| 2 | Repeat 1.1 multiple times with different arguments | |

| N | exit | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Execute ``exit`` command | with/without arguments |
| 1.1 | exit | exit 1 |
| 2 | Repeat multiple times with different arguments | |
| 3 | Don't forget to relaunch the minishell | |

| N | Return value of a process | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Execute a simple command with an absolute path with/without any quotes or double quotes | use commands in /bin directory, with/without arguments |
| 2 | Then execute ``echo $?`` and check the printed value | do the same in bash in order to compare the results |
| 3 | Repeat multiple times with different commands and arguments | Try some wrong commands |
| 4 | Try anything like expr $? + $? | do the same in bash in order to compare the results |

| N | Signals | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | ctrl-C | in an empty prompt should display a new line with a new prompt |
| 2 | ctrl-C | in a prompt after you wrote some stuff should display a new line with a new prompt |
| 3 | ctrl-C | after running a blocking command like cat without arguments or grep “something“ |
| 4 | ctrl-D | in an empty prompt should quit minishell --> RELAUNCH! |
| 5 | ctrl-D | in a prompt after you wrote some stuff should not do anything |
| 6 | ctrl-D | after running a blocking command like cat without arguments or grep “something“ |
| 7 | ctrl-\ | in an empty prompt should not do anything |
| 8 | ctrl-\ | in a prompt after you wrote some stuff should not do anything |
| 9 | ctrl-\ | after running a blocking command like cat without arguments or grep “something“ |
| 10 | The buffer should be clean too | Press ``Enter`` to make sure nothing from the previous line is executed |
| 11 | Repeat multiple times using different commands |  |

| N | Double Quotes | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Execute a simple command with arguments and, this time, use also double quotes | you should try to include whitespaces too |
| 2 | Try a command like : ``echo "cat lol.c | cat > lol.c"`` |
| 3 | Try anything except ``$`` |

## From here there is no need to fail using flags

| N | Simple Quotes | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Execute commands with single quotes as arguments |  |
| 2 | Try empty arguments |
| 3 | ``echo '$USER'`` must print ``$USER`` |  |
| 4 | Nothing should be interpreted |  |

| N | env | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Check if env shows you the current environment variables | ``env`` |

| N | export | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Export environment variables, create new ones and replace old ones | ``export a=`` after env ``unset a=`` |
| 2 | Check the result with env | ``env`` |

| N | unset | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Export environment variables, create new ones and replace old ones | ``export a=`` after check env ``unset a=`` |
| 2 | Use ``unset`` to remove some of them | ``unset PWD`` after check env |
| 3 | Check the result with env | ``env`` |

| N | cd | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Use the command cd to move the working directory | check if you are in the right directory with ``/bin/ls`` |
| 2 | Repeat multiple times with working and not working cd |  |
| 3 | Also, try ``.`` and ``..`` as arguments | ``cd .`` or ``cd ..`` |

| N | pwd | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Use the command | ``pwd`` |
| 2 | Repeat multiple times in different directories |  |

| N | Relative Path | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Execute commands but this time use a relative path | ``/.../cmd`` |
| 2 | Repeat multiple times in different directories with a complex relative path (lots of ..) |  |

| N | Environment Path | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Execute commands but this time without any path | ls, wc, awk and so forth |
| 2 | Unset the $PATH and ensure commands are not working anymore |  |
| 3 | Set the $PATH to a multiple directory value (directory1:directory2) and ensure that directories are checked in order from left to right ||

| N | Redirection | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Execute commands with redirections ``<`` and/or ``>`` |  |
| 2 | Repeat multiple times with different commands and arguments and sometimes change ``>`` with ``>>`` |  |
| 3 | Check if multiple tries of the same redirections fail |  |
| 4 | Test << redirection | it doesn't have to update the history |

| N | Pipes | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Execute commands with pipes | cat file | grep bla | more |
| 2 | Repeat multiple times with different commands and arguments |  |
| 3 | Try some wrong commands | ``ls filethatdoesntexist | grep bla | more`` |
| 4 | Try to mix pipes and redirections |  |

❎

| N | Go Crazy and history | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Type a command line, then use ``ctrl-C`` and press "Enter" | The buffer should be clean and there should be nothing left to execute |
| 2 | Can we navigate through history using Up and Down? Can we retry some command? | Answer |
| 3 | Execute commands that should not work like 'dsbksdgbksdghsd'. Ensure minishell doesn't crash and print an error |  |
| 4 | ``cat | cat | ls`` should behave in a "normal way" |  |
| 5 | Try to execute a long command with a ton of arguments |  |
| 6 | Have fun with that beautiful minishell and enjoy it! |  |

❎

| N | Environment Variables | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Execute ``echo`` with some environment variables ($variable) as arguments |  |
| 2 | Check that ``$`` is interpreted as an environment variable |  |
| 3 | Check that double quotes interpolate ``$`` |  |
| 4 | Check that USER exists. Otherwise, set it |  |
| 5 | ``echo "$USER"`` should print the value of the USER variable |  |

## BONUS - if Mandatory perfect

| N | And, Or | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Use ``&&``, ``||`` and parenthesis with commands and ensure minishell behaves the same way bash does |  |

| N | WildCard | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Use wildcards in arguments in the current working directory |  |

| N | Surprise (or not...) | Cases |
| :-----: | :-------------: | :-------------: |
| 1 | Set the USER environment variable |  |
| 2 | ``echo "'$USER'"`` should print the value of the USER variable |  |
| 3 | ``echo '"$USER"'`` should print ``"$USER"`` |  |

