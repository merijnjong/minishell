/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:50:45 by mjong             #+#    #+#             */
/*   Updated: 2024/11/06 15:36:46 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	greater_than(char **cmd, int i)
{
	int	fd;

	fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("Error opening file"), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	cmd[i] = NULL;
	return (0);
}

int right_shift(char **cmd, int i)
{
	int	fd;

	fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("Error opening file"), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	cmd[i] = NULL;
	return (0);
}

int	lesser_than(char **cmd, int i)
{
	int	fd;

	fd = open(cmd[i + 1], O_RDONLY);
	if (fd == -1)
		return (perror("Error opening file"), 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	cmd[i] = NULL;
	return (0);
}

int	handle_redirects(char **cmd)
{
	int result;
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], ">") == 0)
			result = greater_than(cmd, i);
		else if (ft_strcmp(cmd[i], ">>") == 0)
			result = right_shift(cmd, i);
		else if (ft_strcmp(cmd[i], "<") == 0)
			result = lesser_than(cmd, i);
		i++;
	}
	return (result);
}
