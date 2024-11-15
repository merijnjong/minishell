/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:50:33 by mjong             #+#    #+#             */
/*   Updated: 2024/11/15 14:33:09 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int process(t_minishell *minishell, t_cmdlist *cmdlist, char **envp)
// {
//     t_node		*current;
//     t_minishell	*cmd;
//     // pid_t		pid;

// 	envp = NULL;
//     current = cmdlist->head;
//     while (current)
//     {
//         cmd = current->cmd;
//         // if (ft_strchr(cmd->command, '|'))
//         // {
//         //     ft_call_pipe(cmdlist, cmd->arguments, envp);
//         //     break ;
// 		// }
//         minishell->status = builtin_check(minishell, cmd);
//         if (minishell->status != 127)
//         {
//             current = current->next;
//             continue ;
//         }
//         // pid = fork();
//         // if (pid == -1)
//         //     ft_error("fork");
//         // else if (pid == 0)
//         // {
//         //     ft_execute(cmd->arguments, envp);
//         //     exit(EXIT_FAILURE);
//         // }
//         // else
//         // {
//         //     if (waitpid(pid, &minishell->status, 0) == -1)
//         //         ft_error("waitpid");
//         //     if (WIFEXITED(minishell->status))
//         //         minishell->status = WEXITSTATUS(minishell->status);
//         // }
//         current = current->next;
//     }
//     return (minishell->status);
// }

int process(t_minishell *minishell, t_cmdlist *cmdlist, char *argv, char **envp)
{
	pid_t	pid;

	if (strchr(argv, '|'))
		return (ft_call_pipe(minishell, argv, envp));
	if (ft_strncmp(argv, "exit", 5) == 0)
		ft_exit(argv);
	minishell->status = builtin_check(minishell, cmdlist, argv);
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

// int process(t_minishell *minishell, t_cmdlist *cmdlist, char *argv, char **envp)
// {
// 	t_node	*current;
// 	char 	**arg;

// 	argv = NULL;
// 	envp = NULL;
// 	current = cmdlist->head;
// 	minishell = NULL;
// 	arg = current->cmd->arguments;
// 	print_dbl_ptr(arg);
// 	// minishell->status = builtin_check(minishell, cmdlist);
// 	return (0);
// }

// int	child_process(t_status status, t_envlist *envlist, char *argv, char **envp)
// {
// 	if (strchr(argv, '|'))
// 		return (ft_call_pipe(status, argv, envp));
// 	status.last = builtin_check(status, envlist, argv);
// 	if (status.last != 127)
// 		return (status.last);
// 	ft_execute(argv, envp);
// 	return (status.last);
// }

// int	parent_process(t_status status, t_envlist *envlist, char *argv, char **envp)
// {
// 	pid_t	pid;
// 	int		fd[2];
	
// 	if (ft_strncmp(argv, "exit", 5) == 0)
// 		ft_exit(argv);
// 	if (pipe(fd) == -1)
// 		ft_error("pipe");
// 	pid = fork();
// 	if (pid == -1)
// 		ft_error("fork");
// 	if (pid == 0)
// 		child_process(status, envlist, argv, envp);
// 	close(fd[0]);
// 	waitpid(pid, &status.last, 0);
// 	// while (wait(NULL) != -1)
// 	// 	;
// 	if (WIFEXITED(status.last))
// 		return (WEXITSTATUS(status.last));
// 	return (0);
// }
