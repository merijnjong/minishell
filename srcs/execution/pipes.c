/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:38:52 by mjong             #+#    #+#             */
/*   Updated: 2024/12/19 12:38:23 by mjong            ###   ########.fr       */
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

// // static int	execute_piped_command(t_cmd *cmd, char **envp, int input_fd,
// // 	int output_fd)
// // {
// // 	pid_t	pid;

// // 	pid = fork();
// // 	if (pid == -1)
// // 		return (ft_error("fork"), 1);
// // 	if (pid == 0)
// // 	{
// // 		if (cmd->redirect)
// // 		{
// // 			if (cmd->redirect->type == REDIR_OUT
// // 				|| cmd->redirect->type == REDIR_APPEND)
// // 				output_fd = -1;
// // 			if (cmd->redirect->type == REDIR_IN)
// // 				input_fd = -1;
// // 		}
// // 		run_child_process(cmd, envp, input_fd, output_fd);
// // 	}
// // 	return (run_parent_process(pid, output_fd, input_fd));
// // }

// static int	handle_pipe_iteration(t_node *current, int *pipe_fd,
// 	int *input_fd, char **envp)
// {
// 	int	status;
// 	int	output_fd;

// 	if (current->next && setup_pipe(pipe_fd) != 0)
// 		return (1);
// 	if (current->next == NULL)
// 		output_fd = STDOUT_FILENO;
// 	else
// 		output_fd = pipe_fd[1];
// 	status = execute_piped_command(current->cmd, envp, *input_fd, output_fd);
// 	if (current->next != NULL)
// 		close(pipe_fd[1]);
// 	if (*input_fd != STDIN_FILENO)
// 		close(*input_fd);
// 	if (current->next != NULL)
// 		*input_fd = pipe_fd[0];
// 	return (status);
// }

// int	execute_pipeline(t_cmdlist *cmdlist, char **envp)
// {
// 	t_node	*current;
// 	int		pipe_fd[2];
// 	int		input_fd;
// 	int		status;
// 	pid_t	pid;

// 	current = cmdlist->head;
// 	input_fd = STDIN_FILENO;
// 	status = 0;
// 	while (current != NULL)
// 	{
// 		status = handle_pipe_iteration(current, pipe_fd, &input_fd, envp);
// 		current = current->next;
// 	}
// 	if (input_fd != STDIN_FILENO)
// 		close(input_fd);
// 	pid = waitpid(-1, &status, 0);
// 	while (pid > 0)
// 		pid = waitpid(-1, &status, 0);
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	else
// 		return (1);
// }
