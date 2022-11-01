/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 21:12:42 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/01 21:12:44 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cheking(t_data data)
{
	int		ps;
	int		i;

	ps = data.cmd_line->size;
	i = -1;
	while (i++ < ps)
	{
	if (ps == 1 && ft_strnstr(BUILTINS, data.cmd_line->head->cmd[0], 35))
	{
		ps = 0;
		check_builtins(&data, data.cmd_line->head);
	}
	else
	{
		ps = 0;
		execute(&data);
	}
	}
}

int	check_builtins(t_data *data, t_spl_pipe *tmp)
{
	if (!ft_strcmp(tmp->cmd[0], "cd"))
		printf("✅ exit = %d\n", cd(data, tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "echo"))
		printf("✅ exit = %d\n", echo(tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "env"))
		printf("✅ exit = %d\n", env(data, tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "exit"))
		printf("✅ exit = %d\n", ft_exit(data, tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "export"))
		printf("✅ exit = %d\n", export(data, tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "pwd"))
		printf("✅ exit = %d\n", pwd(data));
	else if (!ft_strcmp(tmp->cmd[0], "unset"))
		printf("✅ exit = %d\n", unset(data, tmp->cmd));
	return (0);
}

int	run_builtins(t_data *data, t_spl_pipe *tmp)
{
	if (!ft_strcmp(tmp->cmd[0], "cd"))
		printf("❎ exit = %d\n", cd(data, tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "echo"))
		printf("❎ exit = %d\n", echo(tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "env"))
		printf("❎ exit = %d\n", env(data, tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "exit"))
		printf("❎ exit = %d\n", ft_exit(data, tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "export"))
		printf("❎ exit = %d\n", export(data, tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "pwd"))
		printf("❎ exit = %d\n", pwd(data));
	else if (!ft_strcmp(tmp->cmd[0], "unset"))
		printf("❎ exit = %d\n", unset(data, tmp->cmd));
	return (0);
}
