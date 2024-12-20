/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:28:25 by mjong             #+#    #+#             */
/*   Updated: 2024/12/20 16:14:48 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_minishell *envlist, char *key)
{
	t_minishell	*current;
	size_t		key_len;

	current = envlist;
	key_len = ft_strlen(key);
	while (current != NULL)
	{
		if (ft_strncmp(current->env, key, key_len) == 0
			&& current->env[key_len] == '=')
			return (current->env + key_len + 1);
		current = current->next_env;
	}
	return (NULL);
}

int	cd_path(char *path)
{
	if (path == NULL)
		return (1);
	if (chdir(path) == -1)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

int	cd_home(t_minishell *envlist)
{
	char	*home;

	home = get_env_value(envlist, "HOME");
	if (home != NULL)
	{
		if (chdir(home) == -1)
		{
			ft_printf("cd: failed to change to home directory\n");
			return (1);
		}
	}
	else
	{
		ft_printf("cd: HOME environment variable not set\n");
		return (1);
	}
	return (0);
}

int	cd(t_minishell *envlist, char **args)
{
	int	result;

	result = 0;
	if (args == NULL || args[0] == NULL || ft_strcmp(args[0], "cd") != 0)
		return (1);
	if (args[1] == NULL || (ft_strcmp(args[1], "~") == 0))
		result = cd_home(envlist);
	else
		result = cd_path(args[1]);
	return (result);
}
