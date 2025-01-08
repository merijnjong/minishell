/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:38:52 by mjong             #+#    #+#             */
/*   Updated: 2025/01/08 19:47:23 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	handle_child_process(t_minishell *minishell, t_node *current, int input_fd,
	int *pipe_fd)
{
	reset_signals_to_default();
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input_fd");
			exit(1);
		}
		close(input_fd);
	}
	if (current->next)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 pipe_fd[1]");
			exit(1);
		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (current->cmd->redirect && handle_redirects(current->cmd) != 0)
		exit(1);
	ft_execute(minishell, current->cmd);
	exit(1);
}

int	wait_for_all_processes(void)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
		pid = waitpid(-1, &status, 0);
	g_in_child = 0;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

void	parent_process_cleanup(int *pipe_fd, int *input_fd)
{
	if (*pipe_fd != STDOUT_FILENO)
		close(*pipe_fd);
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
}

int	process(t_minishell *minishell)
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
	minishell->status = execute_pipeline(minishell, &minishell->cmdlist);
	return (minishell->status);
}
