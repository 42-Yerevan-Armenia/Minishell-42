/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:29:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/24 09:57:03 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <stdlib.h>
// #include <stdio.h>

int	free_arr(char **arr)
{
	if (*arr)
	{
		free(*arr);
		*arr = NULL;
	}
	return (0);
}

// int main()
// {
// 	char *ptr;

// 	// ptr = malloc(1);
// 	ptr = NULL;

// 	ptr = malloc(1);
// 	printf("ptr = %p\n", ptr);
// 	free_arr(&ptr);
// 	// ptr = NULL;
// 	printf("ptr = %p\n", ptr);
// 	free_arr(&ptr);
// 	// free_arr(ptr);
// }