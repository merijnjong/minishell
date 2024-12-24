/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:50:38 by mjong             #+#    #+#             */
/*   Updated: 2024/12/24 13:50:41 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_find_path(char **envp, char *cmd)
{
	char	**paths;
	char	*path;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
	{
		ft_fprintf(2, "%s: PATH not found\n", cmd);
		return (NULL);
	}
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	path = ft_find_path_2(paths, cmd);
	ft_free_dbl(paths);
	return (path);
}

int	ft_execute(t_cmd *cmd, char **envp)
{
	char	*path;

	if (handle_redirects(cmd) != 0)
	{
		ft_fprintf(2, "%s: Redirection error\n", cmd->filename);
		return (1);
	}
	path = ft_find_path(envp, cmd->filename);
	if (path == NULL)
	{
		ft_putstr_fd(" command not found\n", 2);
		return (127);
	}
	if (execve(path, cmd->args, envp) < 0)
	{
		perror("execve");
		free(path);
		return (1);
	}
	free(path);
	return (0);
}
