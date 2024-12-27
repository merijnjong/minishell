/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:33 by mjong             #+#    #+#             */
/*   Updated: 2024/12/20 16:14:43 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (command->args[1] && ft_strcmp(command->args[1], "-n") == 0)
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
