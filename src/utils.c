#include "../includes/minishell.h"

t_list *create_list(void)
{
    t_list  *list;

    list = malloc(sizeof(t_list));
    if (list == NULL)
        exit (1);
    list->head = NULL;
    list->tail = NULL;
    // list->node = NULL;
    return (list);
}
void add_node(t_list *list, char *cmd, char *options)
{
    t_node  *new_node;
    t_node  *tmp;

    new_node = malloc(sizeof(t_node));
    new_node->cmd = malloc(sizeof(char *) * 2);
    if (new_node == NULL)
        exit (1);
    new_node->cmd[0] = cmd;
    new_node->cmd[1] = options;
    new_node->next = NULL;
    new_node->prev = NULL;
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
       new_node->prev = tmp;
       tmp->next = new_node;
    }
}

void print_list(t_node *head)
{
    while (head)
    {
        printf("%s, ", head->cmd[0]);
        printf("%s\n", head->cmd[1]);
        head = head->next;
    }
    
}