/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:38:52 by mjong             #+#    #+#             */
/*   Updated: 2024/12/20 18:45:28 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process_cleanup(int *pipe_fd, int *input_fd)
{
	if (*pipe_fd != STDOUT_FILENO)
		close(*pipe_fd);
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
}

int	process(t_minishell *minishell, char **envp)
{
	t_node	*current;

	if (!minishell->cmdlist.head)
		return (1);
	current = minishell->cmdlist.head;
	if (current->next == NULL)
	{
		minishell->status = builtin_check(minishell, &minishell->cmdlist);
		if (minishell->status != 127)
			return (minishell->status);
	}
	minishell->status = execute_pipeline(&minishell->cmdlist, envp);
	return (minishell->status);
}
