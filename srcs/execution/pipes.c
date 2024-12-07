/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:38:52 by mjong             #+#    #+#             */
/*   Updated: 2024/12/07 16:21:59 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

static int	execute_piped_command(t_cmd *cmd, char **envp, int input_fd, int output_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ft_error("fork"), 1);
	if (pid == 0)
	{
		if (cmd->redirect)
		{
			if (cmd->redirect->type == REDIR_OUT || 
				cmd->redirect->type == REDIR_APPEND)
				output_fd = -1;
			if (cmd->redirect->type == REDIR_IN)
				input_fd = -1;
		}
		run_child_process(cmd, envp, input_fd, output_fd);
	}
	return (run_parent_process(pid, output_fd, input_fd));
}

static int	handle_pipe_iteration(t_node *current, int *pipe_fd, 
	int *input_fd, char **envp)
{
	int	status;

	if (current->next && setup_pipe(pipe_fd) != 0)
		return (1);
	if (current->next == NULL)
		pipe_fd[1] = STDOUT_FILENO;
	status = execute_piped_command(current->cmd, envp, *input_fd, 
		current->next ? pipe_fd[1] : STDOUT_FILENO);
	if (current->next)
	{
		close(pipe_fd[1]);
		if (*input_fd != STDIN_FILENO)
			close(*input_fd);
		*input_fd = pipe_fd[0];
	}
	return (status);
}

int	execute_pipeline(t_cmdlist *cmdlist, char **envp)
{
	t_node	*current;
	int		pipe_fd[2];
	int		input_fd;
	int		status;

	current = cmdlist->head;
	input_fd = STDIN_FILENO;
	status = 0;
	while (current != NULL)
	{
		status = handle_pipe_iteration(current, pipe_fd, &input_fd, envp);
		current = current->next;
	}
	return (status);
}
