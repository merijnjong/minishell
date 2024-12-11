/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:25 by mjong             #+#    #+#             */
/*   Updated: 2024/12/11 16:50:16 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_check(t_minishell *minishell, t_cmdlist *cmdlist)
{
	t_node	*current;
	char	**args;

	current = cmdlist->head;
	if (!current || !current->cmd)
		return (127);
	args = current->cmd->args;
	// print_dbl_ptr(args);
	if (!args || !args[0])
		return (127);
	if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		return (cd(minishell, args));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (echo(minishell, args));
	else if (ft_strcmp(args[0], "env") == 0)
		return (env(minishell));
	else if (ft_strcmp(args[0], "export") == 0)
		return (export(minishell, args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (pwd(args));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (unset(minishell, args));
	return (127);
}
