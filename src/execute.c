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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char const *str)
{
	write(1, str++, 1);
}

void	ft_putnstr(char *str, int n)
{
	int		i;

	i = -1;
	if (n < 0)
	{
		while (str[++i] && i < (int)ft_strlen(str) + n)
			ft_putchar(str[i]);
	}
	else
	{
		while (str[++i] && i < n)
			ft_putchar(str[i]);
	}
}
/*
** Prints out a string on the screen
**
** @param		str		The string to print
** @param		pos		The position at which to start printing
** @return		N/A
*/

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

/*
** Executes the builtin echo command
**
** @param		args		The arguments to pass to echo
** @return		1 on completion
*/

int	echo_builtin(t_data data)
{
	int		i;
	int		n_flag;

	n_flag = 0;
	if (!data.cmd_paths[0])
	{
		write(1, "\n", 1);
		return (1);
	}
	else if (data.cmd_paths[0][0] == '-' && data.cmd_paths[0][1] == 'n' && data.cmd1 == '\0')
		n_flag = 1;
	i = -1;
	if (n_flag)
		++i;
	while (data.cmd_paths[++i])
	{
		echo_out(data.cmd_paths, i);
		if (!data.cmd_paths[i + 1] && !n_flag)
			ft_putchar('\n');
	}
	return (1);
}
