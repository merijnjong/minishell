/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:50:38 by mjong             #+#    #+#             */
/*   Updated: 2025/01/09 11:59:32 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*ft_find_path_2(char **paths, char *cmd)
{
	char	*temp;
	char	*path;
	int		i;

	i = 0;
	while (paths[i] != NULL)
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*ft_find_path(char **environ, char *cmd)
{
	char	**paths;
	char	*path;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (environ[i] && ft_strnstr(environ[i], "PATH=", 5) == 0)
		i++;
	if (!environ[i])
		return (NULL);
	paths = ft_split(environ[i] + 5, ':');
	if (!paths)
		return (NULL);
	path = ft_find_path_2(paths, cmd);
	ft_free_dbl(paths);
	return (path);
}

int	get_env_count(t_minishell *envlist)
{
	int	count;

	count = 0;
	while (envlist)
	{
		count++;
		envlist = envlist->next_env;
	}
	return (count);
}

char	**env_to_2d_array(t_minishell *envlist)
{
	char	**env_array;
	int		env_count;
	int		i;
	int		j;

	env_count = get_env_count(envlist);
	i = 0;
	env_array = (char **)malloc((env_count + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	while (envlist)
	{
		env_array[i] = strdup(envlist->env);
		if (!env_array[i])
		{
			j = 0;
			while (++j < i)
				free(env_array[j]);
			return (free(env_array), NULL);
		}
		i++;
		envlist = envlist->next_env;
	}
	env_array[i] = NULL;
	return (env_array);
}

int	ft_execute(t_minishell *minishell, t_cmd *cmd)
{
	char	*path;
	char	**environ;

	environ = env_to_2d_array(minishell);
	if (handle_redirects(cmd) != 0)
	{
		ft_fprintf(2, "%s: Redirection error\n", cmd->filename);
		return (1);
	}
	path = ft_find_path(environ, cmd->filename);
	if (path == NULL)
	{
		ft_fprintf(2, "%s: command not found\n", cmd->filename);
		return (127);
	}
	if (execve(path, cmd->args, environ) < 0)
	{
		perror("execve");
		free(path);
		return (1);
	}
	free_array(environ);
	free(path);
	return (0);
}
