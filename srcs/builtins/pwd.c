/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:39 by mjong             #+#    #+#             */
/*   Updated: 2024/12/04 17:50:44 by dkros            ###   ########.fr       */
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

int pwd(char **args)
{
    char cwd[PATH_MAX];

    if (args[1] != NULL)
        return (ft_printf("pwd: too many arguments\n"));
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        ft_printf("%s\n", cwd);
    else
        perror("getcwd");
    return (0);
}
