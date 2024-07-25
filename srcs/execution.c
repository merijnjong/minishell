/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:50:38 by mjong             #+#    #+#             */
/*   Updated: 2024/07/25 15:05:26 by mjong            ###   ########.fr       */
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

void	print_envp(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
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

void	ft_execute(char *input, char *envp[])
{
	char	*path;
	char	*argv[3];

	argv[0] = input;
	argv[1] = NULL;
	argv[2] = NULL;
	if (!input)
		ft_error("input");
	path = ft_find_path(envp, input);
	if (path == NULL)
	{
		free(input);
		perror("Incorrect argument");
		exit(127);
	}
	if (execve(path, argv, envp) < 0)
		ft_error("execve");
}
