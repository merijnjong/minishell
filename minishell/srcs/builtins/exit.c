/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:29:37 by mjong             #+#    #+#             */
/*   Updated: 2025/01/08 12:52:23 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	is_numeric_argument(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	calculate_exit_status(char *arg)
{
	long	exit_status;

	exit_status = ft_atol(arg);
	if (exit_status < 0 || exit_status > 255)
	{
		exit_status = exit_status % 256;
		if (exit_status < 0)
			exit_status += 256;
	}
	return ((int)exit_status);
}

int	ft_exit(char **args, t_minishell *minishell)
{
	int	exit_status;

	ft_printf("exit\n");
	if (args[1] == NULL)
	{
		cleanup_minishell(minishell);
		exit(minishell->status);
	}
	if (is_numeric_argument(args[1]))
	{
		exit_status = calculate_exit_status(args[1]);
		if (args[2] != NULL)
		{
			ft_fprintf(2, "exit: too many arguments\n");
			return (1);
		}
		cleanup_minishell(minishell);
		exit(exit_status);
	}
	ft_fprintf(2, "exit: %s: numeric argument required\n", args[1]);
	cleanup_minishell(minishell);
	exit(2);
	return (0);
}
