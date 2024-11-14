/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:28:25 by mjong             #+#    #+#             */
/*   Updated: 2024/11/14 13:42:53 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_envlist *envlist, char *key)
{
	t_envlist	*current;
	size_t		key_len;

	current = envlist;
	key_len = ft_strlen(key);
	while (current)
	{
		if (ft_strncmp(current->env, key, key_len) == 0 && current->env[key_len] == '=')
			return (current->env + key_len + 1);
		current = current->next;
	}
	return (NULL);
}

int	cd_path(char *cd_cmd, int i, int j)
{
	char	*path;

	path = ft_strndup(cd_cmd + i, j - i);
	if (chdir(path) == -1)
	{
		ft_printf("cd: not a directory: %s\n", path);
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

int	cd_home(t_envlist *envlist)
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

int	cd(t_envlist *envlist, char *cd_cmd)
{
	int	result;
	int	i;
	int	j;

	i = 0;
	while (cd_cmd[i] == ' ')
		i++;
	j = ft_strlen(cd_cmd);
	while (j > i && cd_cmd[j - 1] == ' ')
		j--;
	if (i == j || (j - i == 1 && cd_cmd[i] == '~'))
		result = cd_home(envlist);
	else
		result = cd_path(cd_cmd, i, j);
	return (result);
}
