/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:44:08 by mjong             #+#    #+#             */
/*   Updated: 2024/06/20 16:39:58 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input(t_node *cmd)
{
	while (1)
	{
		cmd->cmd = readline("minishell> ");
		parser(cmd->cmd);
		if (cmd->cmd != NULL)
			add_history(cmd->cmd);
		free(cmd->cmd);
		// add clear_history function somewhere
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_node	cmd;

	argv = NULL;
	envp = NULL;
	if (argc > 1)
	{
		input(&cmd);
	}
	else
		ft_printf("Incorrect notation, start program by typing: ./minishell start\n");
	return (0);
}
