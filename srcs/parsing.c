/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:50:33 by mjong             #+#    #+#             */
/*   Updated: 2024/07/25 15:06:34 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser(char *input, char *envp[])
{
	pid_t	pid;
	int		status;

	envp = NULL;
	pid = fork();
	if (pid == -1)
		ft_error("fork");
	else if (pid == 0)
	{
		if (input[0] == '\0')
			return (0);
		else if (ft_strncmp(input, "ls", 3) == 0)
			ft_execute("/usr/bin/ls", envp);
		else
			builtincheck(input);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			ft_error("waitpid");
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (-1);
	}
	return (0);
}
