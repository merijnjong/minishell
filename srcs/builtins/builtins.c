/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:25 by mjong             #+#    #+#             */
/*   Updated: 2024/11/28 16:02:52 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	builtin_check(t_minishell *minishell, char **command)
// {	
// 	if (ft_strcmp(command[0], "exit") == 0)
// 		ft_exit(*command);
// 	if (ft_strcmp(command[0], "cd") == 0)
// 		return (cd(minishell, command[1]));
// 	if (ft_strcmp(command[0], "echo") == 0)
// 		return (echo(minishell, command[1]));
// 	if (ft_strcmp(command[0], "env") == 0)
// 		return (env(minishell));
// 	if (ft_strcmp(command[0], "export") == 0)
// 		return (export(minishell, command[1]));
// 	if (ft_strcmp(command[0], "pwd") == 0)
// 		return (pwd(command[1]));
// 	if (ft_strcmp(command[0], "unset") == 0)
// 		return (unset(minishell, command[1]));
// 	else
// 		return (127);
// }

int	builtin_check(t_minishell *minishell, t_cmdlist *cmdlist)
{	
	t_node	*current;
	char	**command;
	
	current = cmdlist->head;
	command = current->cmd->arguments;

	if (ft_strcmp(command[0], "exit") == 0)
		ft_exit(command[0]);
	if (ft_strcmp(command[0], "cd") == 0)
		return (cd(minishell, command[1]));
	if (ft_strcmp(command[0], "echo") == 0)
		return (echo(minishell, command[1]));
	if (ft_strcmp(command[0], "env") == 0)
		return (env(minishell));
	if (ft_strcmp(command[0], "export") == 0)
		return (export(minishell, command[1]));
	if (ft_strcmp(command[0], "pwd") == 0)
		return (pwd(command[1]));
	if (ft_strcmp(command[0], "unset") == 0)
		return (unset(minishell, command[1]));
	else
		return (127);
}
