/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_processes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:50:33 by mjong             #+#    #+#             */
/*   Updated: 2024/11/14 16:32:17 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int process(t_minishell *minishell, char *argv, char **envp)
{
	pid_t	pid;

	if (strchr(argv, '|'))
		return (ft_call_pipe(minishell, argv, envp));
	if (ft_strncmp(argv, "exit", 5) == 0)
		ft_exit(argv);
	minishell->status = builtin_check(minishell, argv);
	if (minishell->status != 127)
		return (minishell->status);
	pid = fork();
	if (pid == -1)
		ft_error("fork");
	else if (pid == 0)
	{
		ft_execute(argv, envp);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (waitpid(pid, &minishell->status, 0) == -1)
			ft_error("waitpid");
		if (WIFEXITED(minishell->status))
			return (WEXITSTATUS(minishell->status));
	}
	return (0);
}

// // int	child_process(t_status status, t_envlist *envlist, char *argv, char **envp)
// // {
// // 	if (strchr(argv, '|'))
// // 		return (ft_call_pipe(status, argv, envp));
// // 	status.last = builtin_check(status, envlist, argv);
// // 	if (status.last != 127)
// // 		return (status.last);
// // 	ft_execute(argv, envp);
// // 	return (status.last);
// // }

// // int	parent_process(t_status status, t_envlist *envlist, char *argv, char **envp)
// // {
// // 	pid_t	pid;
// // 	int		fd[2];
	
// // 	if (ft_strncmp(argv, "exit", 5) == 0)
// // 		ft_exit(argv);
// // 	if (pipe(fd) == -1)
// // 		ft_error("pipe");
// // 	pid = fork();
// // 	if (pid == -1)
// // 		ft_error("fork");
// // 	if (pid == 0)
// // 		child_process(status, envlist, argv, envp);
// // 	close(fd[0]);
// // 	waitpid(pid, &status.last, 0);
// // 	// while (wait(NULL) != -1)
// // 	// 	;
// // 	if (WIFEXITED(status.last))
// // 		return (WEXITSTATUS(status.last));
// // 	return (0);
// // }
