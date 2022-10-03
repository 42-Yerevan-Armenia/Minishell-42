#include "../includes/minishell.h"

/*
Checks if the first word in the input is one of the builtin commands, if it
is, it executes it and returns -1, 0, or 1


int	check_binar(char **cmd)
{}

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

int execute(char **cmd)
{
	int	is_builtin;

	if ((is_builtin = check_builtin(cmd)) == 1 || check_binar(cmd))
		return (0);
	if (is_builtin < 0)
		return (-1);
	return (0);
}
*/