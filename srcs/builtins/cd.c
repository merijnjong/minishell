/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:28:25 by mjong             #+#    #+#             */
/*   Updated: 2024/11/21 18:19:36 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_minishell *envlist, char *key)
{
	t_minishell	*current;
	size_t		key_len;

	current = envlist;
	key_len = ft_strlen(key);
	while (current)
	{
		if (ft_strncmp(current->env, key, key_len) == 0 && current->env[key_len] == '=')
			return (current->env + key_len + 1);
		current = current->next_env;
	}
	return (NULL);
}

int	cd_path(char *command)
{
	char	*path;

	path = ft_strdup(command);
	if (chdir(path) == -1)
	{
		ft_printf("cd: not a directory: %s\n", path);
		free(path);
		return (1);
	}
	free(path);
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

int	cd(t_minishell *envlist, char *command)
{
	int	result;

	result = 0;
	if (command == NULL || *command == '\0' || (*command == '~' && *(command + 1) == '\0'))
		result = cd_home(envlist);
	else if (command[1])
		result = cd_path(command);
	return (result);
}
