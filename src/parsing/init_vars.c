#include "minishell.h"


void	init_vars(t_vars *v, int i, int j, int k)
{
	v->i = i;
	v->j = j;
	v->k = k;
	v->c = 0;
	v->t = 0;
}