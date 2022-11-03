/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:32:24 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/03 19:04:30 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_quotes(char *arr)
{
	int	i;
	int	count;

	if (arr == NULL)
		return (0);
	i = 0;
	count = 0;
	while (arr[i])
	{
		if (ft_strchr(QUOTES, arr[i]))
			count++;
		i++;
	}
	return (count);
}

static void	clean_quotes_helper(char **res, char *tmp, int *i, int *k)
{
	char	c;
	int		j;

	j = 0;
	while (res[*i][j])
	{
		while (res[*i][j] && !ft_strchr(QUOTES, res[*i][j]))
			tmp[(*k)++] = res[*i][j++];
		if (res[*i][j] == '\0')
			break ;
		c = res[*i][(j)++];
		while (res[*i][j] && res[*i][j] != c)
			tmp[(*k)++] = res[*i][j++];
		if (res[*i][j])
			j++;
	}
}

static int	clean_quotes(char ***arr)
{
	int		i;
	char	**res;
	int		k;
	char	*tmp;

	res = *arr;
	if (*arr == NULL)
		return (0);
	i = 0;
	while (res[i])
	{
		k = 0;
		tmp = malloc(ft_strlen(res[i]) - count_quotes(res[i]) + 1);
		clean_quotes_helper(res, tmp, &i, &k);
		tmp[k] = '\0';
		free_arr(&res[i]);
		res[i] = tmp;
		i++;
	}
	return (0);
}

int	ft_clean_all_qutoes(t_spl_pipe *head)
{
	while (head)
	{
		clean_quotes(&head->cmd);
		clean_quotes(&head->heredoc);
		// clean_quotes(&head->rdc); // nayel
		head = head->next;
	}
	return (0);
}

int	clean_quotes_single_arr(char **s)
{
	char	c;
	int		i;
	char	*res;
	char	*tmp;

	i = 0;
	tmp = *s;
	res = malloc(ft_strlen(tmp) + 1);
	while (*tmp)
	{
		while (*tmp && !ft_strchr(QUOTES, *tmp))
			res[i++] = *tmp++;
		if (*tmp == '\0')
			break ;
		c = *tmp++;
		while (*tmp && *tmp != c)
			res[i++] = *tmp++;
		if (*tmp)
			tmp++;
	}
	res[i] = '\0';
	*s = res;
	return (0);
}