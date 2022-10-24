/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:32:24 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/24 20:40:46 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_quotes(char *arr)
{
	int i;
	int count;

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

static int	clean_quotes(char ***arr)
{
	int i;
	char **res = *arr;
	int j;
	int k;
	char *tmp;
	char c;

	if (*arr == NULL)
		return (0);
	i = 0;
	// printf("%s\n", res[0]);
	// printf("%s\n", res[1]);
	while (res[i])
	{
		j = 0;
		k = 0;
		// printf("count_quotes(res[i]) = %d\n", count_quotes(res[i]));
		tmp = malloc(ft_strlen(res[i]) - count_quotes(res[i]) + 1);
		while (res[i][j])
		{
			while (res[i][j] && !ft_strchr(QUOTES, res[i][j]))
				tmp[k++] = res[i][j++];
			if (res[i][j] == '\0')
				break;
			c = res[i][j++];
			while (res[i][j] && res[i][j] != c)
				tmp[k++] = res[i][j++];
			if (res[i][j])
				j++;
		}
		tmp[k] = '\0';
		// printf("tmp = %s\n", tmp);
		free_arr(&res[i]);
		res[i] = tmp;
		i++;
	}
	return (0);
}

int ft_clean_all_qutoes(t_spl_pipe *head)
{
	while (head)
	{
		clean_quotes(&head->cmd);
		clean_quotes(&head->heredoc);
		clean_quotes(&head->in_files);
		clean_quotes(&head->out_files);
		head = head->next;
	}
	return (0);
}