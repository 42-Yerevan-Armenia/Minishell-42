/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:33:40 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/03 15:22:32 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && --n)
	{
		if (*s1 != *s2)
		{
			break ;
		}
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	char	*ptr1;

	ptr = (char *) malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (ptr == 0)
		return (0);
	ptr1 = ptr;
	if (!ptr)
		return (0);
	while (*s1 != '\0')
		*ptr++ = *s1++;
	while (*s2 != '\0')
		*ptr++ = *s2++;
	*ptr = '\0';
	return (ptr1);
}

char	*ft_substr(char const *src, unsigned int start, size_t len)
{
	char	*ptr;
	int		i;
	size_t	s_len;

	s_len = ft_strlen(src + start);
	if (start >= (unsigned int)ft_strlen(src))
	{
		ptr = malloc(sizeof(char));
		ptr[0] = '\0';
		return (ptr);
	}
	if (s_len < len)
		len = s_len;
	ptr = (char *) malloc(len + 1);
	if (ptr == 0)
		return (0);
	i = 0;
	while (src[start] && len--)
		ptr[i++] = src[start++];
	ptr[i] = '\0';
	return (ptr);
}

int	mal_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	if (str)
		free(str);
	return (1);
}

static int	counting_word(char const *s, char c)
{
	int	index;
	int	count;

	count = 0;
	index = 0;
	if (!s && !c)
		return (0);
	while (s[index] != '\0')
	{
		if (s[index] == c && index != 0 && s[index + 1] != c)
			count++;
		index++;
	}
	if (s[index - 1] != c)
		count += 1;
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**splited;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	splited = malloc(8 * counting_word(s, c) + 1);
	if (!splited)
		return (0);
	while (s[i[0]] != '\0')
	{
		i[1] = i[0];
		while (s[i[0]] != '\0' && s[i[0]] != c)
			i[0]++;
		if (!((i[0] == 0 && s[i[0]] == c)))
		{
			splited[i[2]] = ft_substr(s, i[1], i[0] - i[1]);
			if (!splited[i[2]++] && mal_free(splited))
				return (0);
		}
		while (s[i[0]] != '\0' && s[i[0]] == c)
			i[0]++;
	}
	splited[i[2]] = NULL;
	return (splited);
}

char    *get_cmd(char **paths, char *cmd)
{
    char    *tmp;
    char    *command;

    while (*paths)
    {
        tmp = ft_strjoin(*paths, "/");
        command = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(command, F_OK) == 0)
            return (command);
        free(command);
        paths++;
    }
    return (NULL);
}

void find_path(t_data data, char **av)
{
    while (ft_strncmp("PATH", *av, 4))
        *av += 1;
    *av += 5;
    while (data.cmd_line->head)
    {
        data.cmd_paths = ft_split(*av, ':');
        data.pid = fork();
        if (data.pid < 0)
            printf("❌ Error");
        if (data.pid == 0)
        {
            data.cmd_args = ft_split(data.cmd_line->head->cmd, ' ');
            data.cmd1 = get_cmd(data.cmd_paths, data.cmd_args[0]);
            if (!data.cmd1)
            {
                int i = 0;
                while (data.cmd_args[i])
                    free(data.cmd_args[i++]);
                free(data.cmd_args);
                free(data.cmd1);
            }
            execve(data.cmd1, data.cmd_args, av);
            exit(0);
        }
       // else
         //   waitpid(data.pid, NULL, 0);
        data.cmd_line->head = data.cmd_line->head->next;
    }
}

int main(int ac, char **av)
{
    t_data data;

    data.cmd_line = create_list();
    add_node(data.cmd_line, "echo Hello");
    //add_node(data.cmd_line, "|");
    //add_node(data.cmd_line, "wc Makefile");
    find_path(data, av);
    echo_builtin(data);
    //printf("%d\n", __LINE__);
}


