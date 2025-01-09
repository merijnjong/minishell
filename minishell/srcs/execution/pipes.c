/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:38:52 by mjong             #+#    #+#             */
/*   Updated: 2025/01/09 12:20:15 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	create_pipe_if_needed(t_node *current, int *pipe_fd)
{
	if (current->next && pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

static int	execute_command(t_minishell *minishell, t_node *current,
	int *input_fd, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		reset_signals_to_default();
		handle_child_process(minishell, current, *input_fd, pipe_fd);
	}
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	if (current->next)
		close(pipe_fd[1]);
	if (current->next)
		*input_fd = pipe_fd[0];
	else
		*input_fd = STDIN_FILENO;
	return (0);
}

int	execute_pipeline(t_minishell *minishell, t_cmdlist *cmdlist)
{
	t_node	*current;
	int		pipe_fd[2];
	int		input_fd;
	int		status;

	current = cmdlist->head;
	input_fd = STDIN_FILENO;
	g_in_child = 1;
	while (current != NULL)
	{
		if (create_pipe_if_needed(current, pipe_fd) != 0)
			return (1);
		if (execute_command(minishell, current, &input_fd, pipe_fd) != 0)
			return (1);
		current = current->next;
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	status = wait_for_all_processes();
	g_in_child = 0;
	return (status);
}
