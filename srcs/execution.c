/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:50:38 by mjong             #+#    #+#             */
/*   Updated: 2024/08/07 18:14:08 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_dbl(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	print_dbl_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		printf("%s\n", ptr[i]);
		i++;
	}
}

char	*ft_find_path(char *envp[], char *cmd)
{
	char	**paths;
	char	*temp;
	char	*path;
	int		i;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (paths == NULL)
	{
		ft_free_dbl(paths);
		ft_error("paths");
	}
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
	ft_free_dbl(paths);
	return (0);
}

void	ft_execute(char *argv, char *envp[])
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (cmd == NULL)
		ft_error("cmd");
	path = ft_find_path(envp, cmd[0]);
	if (path == NULL)
	{
		ft_free_dbl(cmd);
		perror("Incorrect argument");
		exit(127);
	}
	if (execve(path, cmd, envp) < 0)
		ft_error("execve");
}
