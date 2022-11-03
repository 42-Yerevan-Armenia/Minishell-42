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
/*
void	pipes(t_data *data, int psize, t_spl_pipe *tmp)
{
	char *infile = *tmp->in_files;
	char *outfile = *tmp->out_files;
	int	tmpin = dup(0);
	int	tmpout = dup(1);
	int ret;
	
	if (infile)
		tmp->fd_in = open(infile, O_RDWR); 
	else // Use default input
		tmp->fd_in=dup(tmpin);

	int i = -1;
	while (++i < psize)
	{
		//redirect input
		dup2(tmp->fd_in, 0);
		close(tmp->fd_in);
		//setup output
		if (i == psize - 1)
		{// Last simple command 
    		if(outfile)
				tmp->fd_out =open(outfile, O_TRUNC | O_CREAT | O_RDWR, 0644);
			else // Use default output
				tmp->fd_out =dup(tmpout);
		}
		else
		{
			// Not last 
			//simple command
			//create pipe
			int fdpipe[2];
			
			pipe(fdpipe);
			tmp->fd_in = fdpipe[0];
			tmp->fd_out = fdpipe[1];
		}// if/else
		// Redirect output
		dup2(tmp->fd_out, 1);
		close(tmp->fd_out);
		// Create child process
		ret = fork(); 
		if(ret == 0)
		{
			if (tmp->pid == 0)
				do_cmd(data, tmp, psize);
			perror("Error");
			exit(1);
		}
	}
	//  for
	//restore in/out defaults
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	while (tmp)
	{
		waitpid(tmp->pid, &ret, 0);
		tmp = tmp->next;
	}
	data->exit_status = WEXITSTATUS(ret);
	tmp = data->cmd_line->head;
}
*/
