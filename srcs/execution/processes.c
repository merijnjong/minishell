/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:38:52 by mjong             #+#    #+#             */
/*   Updated: 2024/12/18 15:34:19 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	child_process_setup(int input_fd, int output_fd)
// {
// 	if (input_fd != STDIN_FILENO)
// 	{
// 		dup2(input_fd, STDIN_FILENO);
// 		close(input_fd);
// 	}
// 	if (output_fd != STDOUT_FILENO)
// 	{
// 		dup2(output_fd, STDOUT_FILENO);
// 		close(output_fd);
// 	}
// }

void	parent_process_cleanup(int *pipe_fd, int *input_fd)
{
	if (*pipe_fd != STDOUT_FILENO)
		close(*pipe_fd);
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
}

// int	run_child_process(t_cmd *cmd, char **envp, int input_fd, int output_fd)
// {
// 	int			status;
// 	t_buffer	stdout_buffer;

// 	ft_setvbuf(&stdout_buffer, 1);
// 	if (input_fd != -1)
// 		child_process_setup(input_fd, output_fd);
// 	if (cmd->redirect)
// 		handle_redirects(cmd);
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// 	status = ft_execute(cmd, envp);
// 	flush_buffer(&stdout_buffer, STDOUT_FILENO);
// 	exit (status);
// }

// int	run_parent_process(pid_t pid, int output_fd, int input_fd)
// {
// 	int	status;
// 	int	signal;

// 	parent_process_cleanup(&output_fd, &input_fd);
// 	waitpid(pid, &status, 0);
// 	if (WIFSIGNALED(status))
// 	{
// 		signal = WTERMSIG(status);
// 		if (signal == SIGINT)
// 			write(1, "\n", 1);
// 		else if (signal == SIGQUIT)
// 			write(1, "Quit (core dumped)\n", 20);
// 		return (128 + signal);
// 	}
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	return (1);
// }

int	process(t_minishell *minishell, t_cmdlist *cmdlist, char **envp)
{
	t_node	*current;

	if (!cmdlist || !cmdlist->head)
		return (1);
	current = cmdlist->head;
	if (current->next == NULL)
	{
		minishell->status = builtin_check(minishell, cmdlist);
		if (minishell->status != 127)
			return (minishell->status);
	}
	minishell->status = execute_pipeline(cmdlist, envp);
	return (minishell->status);
}
