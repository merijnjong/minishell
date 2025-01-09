/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:28:25 by mjong             #+#    #+#             */
/*   Updated: 2025/01/09 11:40:45 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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

int	change_directory(char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

int	cd_path(char *path, t_minishell *envlist)
{
	char	*pwd;

	pwd = get_env_value(envlist, "PWD");
	if (!pwd)
		return (change_directory(path));
	update_env(envlist, "OLDPWD", pwd);
	if (path == NULL)
		return (1);
	if (change_directory(path))
		return (1);
	return (0);
}

int	cd_home(t_minishell *envlist)
{
	char	*home;
	char	*pwd;

	pwd = get_env_value(envlist, "PWD");
	if (pwd)
		update_env(envlist, "OLDPWD", pwd);
	home = get_env_value(envlist, "HOME");
	if (home != NULL)
	{
		if (chdir(home) == -1)
		{
			ft_fprintf(2, "cd: failed to change to home directory\n");
			return (1);
		}
	}
	else
	{
		ft_fprintf(2, "cd: HOME environment variable not set\n");
		return (1);
	}
	return (0);
}

int	cd(t_minishell *envlist, char **args)
{
	int		result;
	char	*path;
	char	cwd[PATH_MAX];

	result = 0;
	if (args == NULL || args[0] == NULL || ft_strcmp(args[0], "cd") != 0)
		return (1);
	if (args[1] == NULL || (ft_strcmp(args[1], "~") == 0))
		result = cd_home(envlist);
	else if ((ft_strcmp(args[1], "-") == 0))
	{
		path = ft_strdup(get_env_value(envlist, "OLDPWD"));
		result = cd_path(path, envlist);
		free(path);
	}
	else if (args[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	else
		result = cd_path(args[1], envlist);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_setenv(envlist, "PWD", cwd);
	return (result);
}
