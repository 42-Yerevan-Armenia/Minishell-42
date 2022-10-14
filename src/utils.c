#include "../includes/minishell.h"


t_list *create_list(void)
{
    t_list  *list;

    list = malloc(sizeof(t_list));
    if (list == NULL)
        exit (1);
    list->head = NULL;
    list->tail = NULL;
    list->node = NULL;
    return (list);
}
void add_node_1(t_list *list, char *cmd)
{
    t_node  *new_node;
    t_node  *tmp;

    new_node = malloc(sizeof(t_node));
    if (new_node == NULL)
        exit (1);
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
