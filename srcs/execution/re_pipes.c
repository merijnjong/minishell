/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:50:26 by mjong             #+#    #+#             */
/*   Updated: 2024/12/18 17:50:29 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pipeline(t_cmdlist *cmdlist, char **envp)
{
	t_node	*current;
	int		pipe_fd[2];
	int		input_fd;
	int		status;
	pid_t	pid;

	current = cmdlist->head;
	input_fd = STDIN_FILENO;

	while (current != NULL)
	{
		if (current->next && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return (1);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (1);
		}

		if (pid == 0)
		{
			if (input_fd != STDIN_FILENO)
			{
				dup2(input_fd, STDIN_FILENO);
				close(input_fd);
			}
			if (current->next)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			if (current->cmd->redirect && handle_redirects(current->cmd) != 0)
				exit(1);
			ft_execute(current->cmd, envp);
			exit(1);
		}
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (current->next)
			close(pipe_fd[1]);
		input_fd = (current->next) ? pipe_fd[0] : STDIN_FILENO;
		current = current->next;
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	while (pid > 0)
		pid = waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (1);
}
