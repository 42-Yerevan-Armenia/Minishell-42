/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:27:35 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/25 11:05:50 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_1(char *s1, char *s2)
{
	char	*ptr;
	char	*ptr1;
	char	*arr_to_free;

	arr_to_free = s1;
	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen((char *)s2) + 1);
	if (ptr == 0 && !ft_perror("🔻minishell: "))
		exit (0);
	ptr1 = ptr;
	while (s1 && *s1 != '\0')
		*ptr++ = *s1++;
	while (s2 && *s2 != '\0')
		*ptr++ = *s2++;
	*ptr = '\0';
	free_arr(&arr_to_free);
	return (ptr1);
}

char	*ft_strjoin_2(char *s1, char *s2)
{
	char	*ptr;
	char	*ptr1;
	char	*arr_to_free;

	arr_to_free = s2;
	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen((char *)s2) + 1);
	if (ptr == 0 && !ft_perror("🔻minishell: "))
		exit (0);
	ptr1 = ptr;
	while (s1 && *s1 != '\0')
		*ptr++ = *s1++;
	while (s2 && *s2 != '\0')
		*ptr++ = *s2++;
	*ptr = '\0';
	free_arr(&arr_to_free);
	return (ptr1);
}
