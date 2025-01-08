/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:33 by mjong             #+#    #+#             */
/*   Updated: 2025/01/08 12:52:17 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	print_arguments(char **args, int start_index, int newline)
{
	int	i;

	i = start_index;
	while (args[i] != NULL)
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
}

static int	is_valid_n_flag(const char *arg)
{
	int	i;

	i = 2;
	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(t_cmd *command)
{
	int	newline;
	int	i;
	int	saved_stdout;

	if (!command || !command->args)
		return (1);
	saved_stdout = dup(STDOUT_FILENO);
	if (handle_redirects(command) != 0)
		return (1);
	newline = 1;
	i = 1;
	while (command->args[i] && is_valid_n_flag(command->args[i]))
	{
		newline = 0;
		i++;
	}
	print_arguments(command->args, i, newline);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		close(saved_stdout);
		return (perror("Error restoring STDOUT"), 1);
	}
	close(saved_stdout);
	return (0);
}
