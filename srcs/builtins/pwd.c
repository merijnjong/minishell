/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:39 by mjong             #+#    #+#             */
/*   Updated: 2024/12/19 13:55:39 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isprint2(char c)
{
	if (c >= 33 && c <= 126)
	{
		return (1);
	}
	return (0);
}

int	pwd(char **args)
{
	char	cwd[PATH_MAX];

	if (args[1] != NULL)
	{
		if (ft_strcmp(args[1], "oi") == 0)
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
				ft_printf("%s\n", cwd);
		}
		else
			return (ft_printf("pwd: too many arguments\n"));
	}
	else
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			ft_printf("%s\n", cwd);
		else
			perror("getcwd");
	}
	return (0);
}
