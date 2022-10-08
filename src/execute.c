#include "../includes/minishell.h"

/*
Checks if the first word in the input is one of the builtin commands, if it
is, it executes it and returns -1, 0, or 1

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
*/

// Prints out a string on the screen

static void		echo_out(char **str, int pos)
{
	int		starts_with;
	int		ends_with;
	int		str_len;

	starts_with = IS_QUOTE(str[pos][0]);
	str_len = (int)ft_strlen(str[pos]);
	ends_with = IS_QUOTE(str[pos][str_len - 1]);
	if (ends_with && starts_with)
		ft_putnstr(str[pos] + 1, -1);
	else if (ends_with)
		ft_putnstr(str[pos], -1);
	else if (starts_with)
		ft_putstr(str[pos] + 1);
	else
		ft_putstr(str[pos]);
	if (str[pos + 1])
		ft_putchar(' ');
}

int	echo_builtin(char **args)
{
	int		i;
	int		n_flag;

	n_flag = 0;
	if (!args[0])
	{
		write(1, "\n", 1);
		return (1);
	}
	else if (args[0][0] == '-' && args[0][1] == 'n' && args == '\0')
		n_flag = 1;
	i = -1;
	if (n_flag)
		++i;
	while (args[++i])
	{
		echo_out(args, i);
		if (!args[i + 1] && !n_flag)
			ft_putchar('\n');
	}
	return (1);
}
