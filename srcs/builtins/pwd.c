/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:39 by mjong             #+#    #+#             */
/*   Updated: 2024/07/25 15:04:15 by mjong            ###   ########.fr       */
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
	int		i;

	i = 0;
	while (ft_isprint2(command[i]) == 1)
		i++;
	if (i == 0)
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
