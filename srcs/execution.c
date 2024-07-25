/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:50:38 by mjong             #+#    #+#             */
/*   Updated: 2024/07/25 17:19:12 by mjong            ###   ########.fr       */
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
	i = 0;
	while (paths[i] != NULL)
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, X_OK) == 0)
		{
			ft_free_dbl(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_dbl(paths);
	return (0);
}

// envp isn't passed on correctly

void	ft_execute(char *input, char *envp[])
{
	char	*path;
	char	**argv;

	if (!input)
		ft_error("input");
	argv = ft_split(input, ' ');
	print_dbl_ptr(argv);
	if (argv == NULL || argv[0] == NULL)
	{
		ft_free_dbl(argv);
		ft_error("split");
	}
	path = ft_find_path(envp, input);
	printf("path: %s\n", path);
	if (path == NULL)
	{
		free(input);
		perror("Incorrect argument");
		exit(127);
	}
	if (execve(path, argv, envp) < 0)
		ft_error("execve");
}
