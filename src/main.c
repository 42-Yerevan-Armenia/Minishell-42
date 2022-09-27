/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:33:40 by vaghazar          #+#    #+#             */
/*   Updated: 2022/09/27 12:44:12 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av)
{
    t_data data;

    data.cmd_line = create_list();
    add_node(data.cmd_line, "ls");
    printf("%s\n", data.cmd_line->head->cmd);
    // dis_prompt();
    // readline("minishell");
}



void add_node(t_list *list, char *cmd)
{
    t_node  *new_node;
    t_node  *tmp;

    new_node = malloc(sizeof(t_list));
    new_node->cmd = cmd;
    new_node->next = NULL;
    if (list->head == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else 
    {
        tmp = list->head;
        while (tmp->next)
            tmp = tmp->next;
       tmp->next = new_node;
    }
}

t_list *create_list(void)
{
    t_list  *list;

    list = malloc(sizeof(t_list));
    list->head = NULL;
    list->tail = NULL;
    list->node = NULL;
    return (list);
}