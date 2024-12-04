/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:50:33 by mjong             #+#    #+#             */
/*   Updated: 2024/11/21 18:18:01 by mjong            ###   ########.fr       */
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

int process(t_minishell *minishell, t_cmdlist *cmdlist, char *argv, char **envp)
{
	pid_t	pid;

	if (strchr(argv, '|'))
		return (ft_call_pipe(minishell, argv, envp));
	minishell->status = builtin_check(minishell, cmdlist);
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
