/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:50:33 by mjong             #+#    #+#             */
/*   Updated: 2024/07/10 17:27:54 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser(char *input, char *envp[])
{
	if (input[0] == '\0')
	{
		ft_printf("\033[31mERROR: Enter a command\e[0m\n");
		return (0);
	}
	else if (ft_strncmp(input, "exit", 5) == 0)
	{
		ft_printf("exit\n");
		return (1);
	}
	else if (ft_strncmp(input, "ls", 3) == 0)
		ft_execute("/usr/bin/ls", envp);
	else
		return (builtincheck(input));
	return (0);
}
