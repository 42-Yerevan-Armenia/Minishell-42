/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:29:53 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/13 13:34:49 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 1;

// int	ft_cmp_lower(char *s2, char *s1)
// {
// 	char	*res;
// 	int		i;

// 	i = 0;
// 	while (s1 && s2 && s1[i])
// 	{
// 		if (s1[i] != ft_tolower(s2[i]))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int	put_underscore(t_data *data)
// {
// 	t_spl_pipe	*tmp;
// 	int			flag;

// 	tmp = data->cmd_line->head;
// 	flag = 0;
// 	data->path = get_val(data->env->head, "PATH", ENV);
// 	if (data->path)
// 		data->cmd_paths = ft_split(data->path, ':');
// 	while (tmp)
// 	{
// 		if (!ft_cmp_lower(*tmp->cmd, "env") && ++flag)
// 			break ;
// 		tmp = tmp->next;
// 	}
// 	if (tmp && flag != 0)
// 	{
// 		if (!ft_strcmp(*tmp->cmd, "env"))
// 			set_env(data, new_env("_=", "env", (ENV)));
// 		else if (data->path && data->cmd_paths)
// 		{
// 			if (get_cmd(data->cmd_paths, *tmp->cmd, data) != NULL)
// 				set_env(data, new_env("_=", get_cmd(data->cmd_paths, *tmp->cmd, data), (ENV)));
// 		}
// 	}
// 	return (0);
// }

static int	ft_readline_main(t_parse *parser, t_data *data)
{
	set_term_attr(TC_OFF);
	parser->rd_ln = readline("🔻minishell> ");
	if (g_sig == 0 && ++g_sig && !free_arr(&parser->rd_ln))
	{
		set_env(data, new_env("?=", "1", FORME));
		return (1);
	}
	set_term_attr(TC_ON);
	if (!parser->rd_ln)
		exit(1);
	return (0);
}

static void	start(t_parse *parser, t_data *data)
{
	while (!free_arr(&parser->rd_ln))
	{
		printf("env = %zu\n", data->env->size);
		printf("env_exp = %zu\n", data->env_exp->size);
		if (ft_readline_main(parser, data) == 1)
			continue ;
		if (parser->rd_ln[0])
		{
			add_history(parser->rd_ln);
			if (parsing(parser) == START_RD_LN
				&& !ft_get_status_in_env(data, parser))
				continue ;
			if (data->cmd_line->head && data->cmd_line->head->cmd)
			{
				execute(data);
			}
		}
		ft_get_status_in_env(data, parser);
	}	
}

int	main(int ac, char **av, char **envp)
{
	t_parse	parser;
	t_data	data;

	(void)av;
	data.builtins = ft_bultins();
	if (ac == 1)
	{
		init(&parser, &data, envp);
		hook_signals();
		start(&parser, &data);
		free_envp(&data.env);
	}
	return (0);
}
