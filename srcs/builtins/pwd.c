/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:39 by mjong             #+#    #+#             */
/*   Updated: 2024/11/28 16:04:02 by mjong            ###   ########.fr       */
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

int	pwd(char *command)
{
	char	cwd[PATH_MAX];

	if (command == NULL)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			ft_printf("%s\n", cwd);
		else
			perror("getcwd");
	}
	else
		return (ft_printf("pwd: too many arguments\n"));
	return (0);
}
