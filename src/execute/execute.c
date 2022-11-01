/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:09:43 by arakhurs          #+#    #+#             */
/*   Updated: 2022/10/31 13:40:38 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	tmp = 0;
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		if (access(command, F_OK) == 0)
			return (command);
		paths++;
	}
	return (NULL);
}

void	close_fds(int (*fds)[2], int psize)
{
	int	i;

	i = -1;
	while (++i < psize - 1)
	{
		if (close(fds[i][1]) == -1)
			perror("CLOSE FAILED");
		if (close(fds[i][0]) == -1)
			perror("CLOSE FAILED");
	}
	free(fds);
}

void	open_pipes(int i, int (*fds)[2], int psize)
{
	if (i == 0)
	{
		if (dup2(fds[0][1], 1) < 0)
			exit(1);
	}
	else if (psize - 1 == i)
	{
		if (dup2(fds[i - 1][0], 0) < 0)
			exit(1);
	}
	else
	{
		dup2(fds[i - 1][0], 0);
		dup2(fds[i][1], 1);
	}
	close_fds(fds, psize);
}

void	do_cmd(t_data *data, t_spl_pipe *tmp, int psize)
{
	int	i;

	i = 0;
	if (ft_strnstr(BUILTINS, tmp->cmd[0], 35))
		run_builtins(data, tmp);
	else
	{
		if (access(*tmp->cmd, F_OK) == 0)
			data->path = *tmp->cmd;
		else if (ft_strchr(*tmp->cmd, '/'))
			printf(NOT_FOUND, *tmp->cmd);
		else
			data->path = get_cmd(data->cmd_paths, *tmp->cmd);
		if (!data->path)
			free(data->path);
		execve(data->path, tmp->cmd, &tmp->cmd[0]);
		printf(NOT_FOUND, *tmp->cmd);
	}
	exit(1);
}

void	forking(int (*fds)[2], int psize, t_spl_pipe *tmp, t_data *data)
{
	int	i;

	i = -1;
	while (++i < psize - 1)
		if (pipe(fds[i]) == -1)
			ft_putstr_fd(INPUT_FILE, 2, FREE_OFF);
	i = 0;
	while (i < psize)
	{
		tmp->pid = fork();
		if (tmp->pid == -1)
			ft_putstr_fd(FORK, 2, FREE_OFF);
		else if (tmp->pid == 0)
		{
			if (psize == 1)
				do_cmd(data, tmp, psize);
			else
			{
				open_pipes(i, fds, psize);
				do_cmd(data, tmp, psize);
			}
		}
		tmp = tmp->next;
		i++;
	}
}

int	execute(t_data *data)
{
	t_spl_pipe	*tmp;
	int			psize;
	int			res;
	int			(*fds)[2];
	int			i;

	tmp = data->cmd_line->head;
	psize = data->cmd_line->size;
	data->path = getenv("PATH");
	data->cmd_paths = ft_split(data->path, ':');
	fds = malloc(sizeof (*fds) * (psize - 1));
	forking(fds, psize, tmp, data);
	close_fds(fds, psize);
	free_double((void *)&data->cmd_paths);
	tmp = data->cmd_line->head;
	while (tmp)
	{
		waitpid(tmp->pid, &res, 0);
		tmp = tmp->next;
	}
	data->exit_status = WEXITSTATUS(res);
	//pipes(data, psize, tmp);
	return (0);
}

void	pipes(t_data *data, int psize, t_spl_pipe *tmp)
{
	char *infile = *tmp->in_files;
	char *outfile = *tmp->out_files;
	int	tmpin = dup(0);
	int	tmpout = dup(1);
	int fdin;
	int fdout;
	int ret;
	
	if (infile)
		fdin = open(infile, O_RDWR); 
	else // Use default input
		fdin=dup(tmpin);

	int i = -1;
	if (++i < psize)
	{
		//redirect input
		dup2(fdin, 0);
		close(fdin);
		//setup output
		if (i == psize - 1)
		{// Last simple command 
    		if(outfile)
				fdout=open(outfile, O_RDWR);
			else // Use default output
				fdout=dup(tmpout);
		}
		else
		{
			// Not last 
			//simple command
			//create pipe
			int fdpipe[2];
			
			pipe(fdpipe);
			fdout=fdpipe[1];
			fdin=fdpipe[0];
		}// if/else
		// Redirect output
		dup2(fdout,1);
		close(fdout);
		// Create child process
		ret = fork(); 
		if(ret == 0)
		{
			execve(data->path, tmp->cmd, &tmp->cmd[0]);
			perror("Error");
			exit(1);
		}
	}
	//  for
	//restore in/out defaults
	dup2(tmpin,0);
	dup2(tmpout,1);
	close(tmpin);
	close(tmpout);
	while (tmp)
	{
		waitpid(tmp->pid, &ret, 0);
		tmp = tmp->next;
	}
	data->exit_status = WEXITSTATUS(ret);
}
