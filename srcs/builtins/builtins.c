/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:25 by mjong             #+#    #+#             */
/*   Updated: 2024/12/04 17:54:07 by dkros            ###   ########.fr       */
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

int builtin_check(t_minishell *minishell, t_cmdlist *cmdlist)
{
    t_node *current;
    char **args;

    current = cmdlist->head;

    // Ensure cmdlist, head, and arguments are valid
    if (!current || !current->cmd || !(args = current->cmd->args) || !args[0])
        return 127; // Command not found

    // Check for builtins and execute
    if (ft_strcmp(args[0], "exit") == 0)
        ft_exit(args); // Typically exits the shell
    else if (ft_strcmp(args[0], "cd") == 0)
        return cd(minishell, args); // Pass entire argument array
    else if (ft_strcmp(args[0], "echo") == 0)
        return echo(minishell, args); // Pass entire argument array
    else if (ft_strcmp(args[0], "env") == 0)
        return env(minishell);
    else if (ft_strcmp(args[0], "export") == 0)
        return export(minishell, args); // Pass entire argument array
    else if (ft_strcmp(args[0], "pwd") == 0)
        return pwd(args); // Pass entire argument array
    else if (ft_strcmp(args[0], "unset") == 0)
        return unset(minishell, args); // Pass entire argument array

    return 127; // Command not recognized as a builtin
}

