#include "../includes/minishell.h"

// int	ft_putstr(char *str)
// {
// 	while (str && *str)
// 		write(1, str++, 1);
// 	return (0);
// }

// static int	mod_env(char **str, char *value)
// {
//   int		i;
//   int		j;
//   char		*new_str;

//   j = 0;
//   i = 0;
//   while (*str && str[0][i] != '=')
//     i += 1;
//   i += 1;
//   if ((new_str = (char*)malloc(ft_strlen(value) + i + 3)) == NULL)
//     return (-1);
//   i = 0;
//   while (*str && str[0][i - 1] != '=')
//     new_str[j++] = str[0][i++];
//   i = 0;
//   while (value[i])
//     new_str[j + i] = value[i++];
//   new_str[j + i] = 0;
//   *str = new_str;
//   return (0);
// }

// static char	**cp_env(char **env)
// {
//   char		**new_env;
//   int		i;

//   i = 0;
//   while (env[i])
//     i = i + 1;
//   if ((new_env = (char**)malloc(sizeof(char*) * i + 2)) == NULL)
//     return (NULL);
//   new_env = env;
//   return (new_env);
// }

// static int	push_env(char ***env, char *variable, char *value)
// {
//   char		**new_env;
//   char		*new_var;
//   int		i;
//   int		j;

//   i = 0;
//   j = 0;
//   if ((new_env = cp_env(*env)) == NULL)
//     return (-1);
//   if ((new_var = (char*)malloc(ft_strlen(value) + ft_strlen(variable) + 2))
//       == NULL)
//     return (-1);
//   while (variable[i])
//     new_var[i] = variable[i++];
//   while (value[j])
//     new_var[j + i] = value[j++];
//   new_var[j + i] = 0;
//   i = 0;
//   while (new_env[i])
//     i = i + 1;
//   new_env[i++] = new_var;
//   new_env[i] = NULL;
//   return (0);
// }

// char	*add_egale(char *var)
// {
//   int	size;
//   char	*new_var;
//   int	i;

//   size = ft_strlen(var);
//   if ((new_var = (char*)malloc(size + 2)) == NULL)
//     return (NULL);
//   i = 0;
//   while (var[i])
//   {
//     new_var[i] = var[i];
//     i = i + 1;
//   }
//   new_var[i++] = '=';
//   new_var[i] = 0;
//   return (new_var);
// }

// int	my_setenv(char ***env, char *variable, char *value)
// {
//   char	**tmp_var;
//   int	i;

//   i = 0;
//   tmp_var = *env;
//   if (variable == NULL || value == NULL)
//     return (ft_putstr("usage: setenv VARIABLE VALUE\n"));
//   if (variable == NULL || ft_strlen(variable) == 0
//       || ft_strchr(variable, '=') != NULL)
//     return (ft_putstr("error : variable NULL or '=' in name\n"));
//   if ((variable = add_egale(variable)) == NULL)
//     return (-1);
//   while (tmp_var && tmp_var[i]
// 	 && ft_strncmp(variable, tmp_var[i], ft_strlen(variable)) != 0)
//     i = i + 1;
//   if (tmp_var == NULL || tmp_var[i] == NULL)
//   {
//     if ((push_env(env, variable, value)) == -1)
//       return (-1);
//   }
//   else if ((mod_env(&tmp_var[i], value)) == -1)
//     return (-1);
//   return (0);
// }

// int	cd_error(char ***tab_env)
// {
//   char	*str;
//   char	*pwd;
//   int	size;

//   size = 200;
//   if (tab_env == NULL)
//     return (-1);
//   if ((str = malloc(sizeof(char) * (size + 1))) == NULL)
//     return (-1);
//   if ((pwd = getcwd(str, size)) != NULL)
//     my_setenv(tab_env, "OLDPWD", pwd);
//   return (0);
// }


// int	main(int ac, char **tab)
// {
// if (ac > 1)
// {
//   if (tab[1] != NULL)
//     {
//       if (access(tab[1], R_OK) == -1 && tab[2] == NULL)
// 	{
// 	  perror(tab[1]);
// 	  return (0);
// 	}
//       else if (access(tab[1], F_OK) == -1 && tab[2] == NULL)
// 	{
// 	  perror(tab[1]);
// 	  return (0);
// 	}
//       else if (chdir(tab[1]) == -1 && tab[2] == NULL)
// 	{
// 	  perror(tab[1]);
// 	  return (0);
// 	}
//       else if (tab[2] != NULL)
// 	{
// 	  write(2, "cd: Too many arguments.\n", 24);
// 	  return (0);
// 	}
//       return (1);
//     }
//    }
//   return (0);
// }
