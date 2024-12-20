/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:38:52 by mjong             #+#    #+#             */
/*   Updated: 2024/12/20 18:44:10 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_pipe_if_needed(t_node *current, int *pipe_fd)
{
	if (current->next && pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

static int	handle_child_process(t_node *current, int input_fd, int *pipe_fd,
	char **envp)
{
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
	ft_execute(current->cmd, envp);
	exit(1);
}

static int	execute_command(t_node *current, int *input_fd, int *pipe_fd,
	char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		handle_child_process(current, *input_fd, pipe_fd, envp);
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

static int	wait_for_all_processes(void)
{
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, 0);
	while (pid > 0)
		pid = waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute_pipeline(t_cmdlist *cmdlist, char **envp)
{
	t_node	*current;
	int		pipe_fd[2];
	int		input_fd;

	current = cmdlist->head;
	input_fd = STDIN_FILENO;
	while (current != NULL)
	{
		if (create_pipe_if_needed(current, pipe_fd) != 0)
			return (1);
		if (execute_command(current, &input_fd, pipe_fd, envp) != 0)
			return (1);
		current = current->next;
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	return (wait_for_all_processes());
}
