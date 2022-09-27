#ifndef STRUCT_H
# define STRUCT_H



typedef struct s_node
{
    char*           cmd;
    struct s_node   *next;

}               t_node;

typedef struct s_list
{
    t_node   *head;
    t_node   *tail;
    t_node          *node;
}               t_list;

typedef struct s_data
{
   t_list   *cmd_line;
}               t_data;
// typedef struct s_syntax
// {
   
// }               t_syntax;
#endif