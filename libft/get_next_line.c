/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:48:27 by vaghazar          #+#    #+#             */
/*   Updated: 2022/05/31 18:55:47 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (1);
		i++;
	}
	return (0);
}

int	read_line(char **tmp_line, int fd)
{
	int		fd_i;
	char	file_read[BUFFER_SIZE + 1];

	fd_i = 1;
	while (fd_i > 0)
	{
		fd_i = read(fd, file_read, BUFFER_SIZE);
		if (((fd_i <= -1) && free_arr(*tmp_line))
			|| ((fd_i == 0 && !*tmp_line) && free_arr(*tmp_line)))
			return (0);
		file_read[fd_i] = '\0';
		*tmp_line = ft_strjoin(*tmp_line, file_read);
		if (ft_strchr(file_read, '\n'))
			break ;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char		*tmp_line;
	int				fd_i;
	char			*line;

	if ((fd < 0 || fd > 65535) || BUFFER_SIZE < 1)
		return (NULL);
	if (!read_line(&tmp_line, fd))
		return (NULL);
	fd_i = 0;
	while (tmp_line[fd_i] != '\n' && tmp_line[fd_i] != '\0')
		fd_i++;
	line = ft_substr(tmp_line, 0, fd_i + 1);
	if (fd_i == 0 && !tmp_line[0] && free_arr(tmp_line))
		return (NULL);
	if (tmp_line[fd_i] == '\0')
		fd_i--;
	tmp_line = ft_strdup(tmp_line + fd_i + 1, tmp_line);
	if (!tmp_line[0] && free_arr(tmp_line))
		tmp_line = NULL;
	return (line);
}
