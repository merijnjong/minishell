/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:50:33 by mjong             #+#    #+#             */
/*   Updated: 2024/12/04 18:12:56 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* char **arguments in structs needs to be appended and turned into char *arguments 
before being returned to execution */

// int process(t_minishell *minishell, t_cmdlist *cmdlist, char **envp)
// {
// 	t_node	*current;
// 	char	**command;
// 	pid_t	pid;

// 	current = cmdlist->head;
// 	while (current)
// 	{
// 		command = current->cmd->arguments;
// 		while (*command)
// 		{
// 			*command = expand_variable(*command, envp);
//			if (ft_strchr(*command, '|'))
// 			{
// 				minishell->status = ft_call_pipe(minishell, *command, envp);
// 				if (minishell->status != 0)
// 					return (minishell->status);
// 				command++;
// 				continue;
// 			}
// 			minishell->status = builtin_check(minishell, command);
// 			if (minishell->status != 127)
// 			{
// 				command++;
// 				continue;
// 			}
// 			pid = fork();
// 			if (pid == -1)
// 				ft_error("fork");
// 			else if (pid == 0)
// 			{
// 				ft_execute(*command, envp);
// 				exit(EXIT_FAILURE);
// 			}
// 			else
// 			{
// 				if (waitpid(pid, &minishell->status, 0) == -1)
// 					ft_error("waitpid");
// 				if (WIFEXITED(minishell->status))
// 					minishell->status = WEXITSTATUS(minishell->status);
// 			}
// 			command++;
// 		}
// 		current = current->next;
// 	}
// 	return (minishell->status);
// }

int process(t_minishell *minishell, t_cmdlist *cmdlist, char **envp)
{
	t_node	*current;
	pid_t	pid;
	int		pipe_fd[2], input_fd = STDIN_FILENO;

	current = cmdlist->head;
	while (current) {
		if (current->next) {
			if (pipe(pipe_fd) == -1) {
				perror("pipe");
				return (1);
			}
		}
		minishell->status = builtin_check(minishell, cmdlist);
		if (minishell->status != 127) {
			return minishell->status; 
		}
		pid = fork();
		if (pid == -1) {
			ft_error("fork");
		} else if (pid == 0) {
			if (input_fd != STDIN_FILENO) {
				dup2(input_fd, STDIN_FILENO);
				close(input_fd);
			}
			if (current->next) {
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			ft_execute(current->cmd, envp);
			exit(EXIT_FAILURE);
		} else {
			if (current->next) {
				close(pipe_fd[1]);
			}
			if (input_fd != STDIN_FILENO) {
				close(input_fd);
			}
			input_fd = pipe_fd[0];
			if (waitpid(pid, &minishell->status, 0) == -1) {
				ft_error("waitpid");
			}
			if (WIFEXITED(minishell->status)) {
				minishell->status = WEXITSTATUS(minishell->status);
			}
		}
		current = current->next;
	}
	return minishell->status;
}

