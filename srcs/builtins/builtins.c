/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:25 by mjong             #+#    #+#             */
/*   Updated: 2024/11/21 14:57:41 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_check(t_minishell *minishell, t_cmdlist *cmdlist, char *input)
{	
	t_node *current;
	
	current = cmdlist->head;

	print_dbl_ptr(current->cmd->arguments);
	// printf("current: %s\n", current->cmd->command);
	while (*input == ' ')
		input++;
	if (ft_strncmp(input, "cd", 2) == 0
		&& (input[2] == ' ' || input[2] == '\0'))
		return (cd(minishell, cmdlist, input + 3));
	else if (ft_strncmp(input, "echo", 4) == 0
		&& (input[4] == ' ' || input[4] == '\0'))
		return (echo(minishell, input + 5));
	else if (ft_strncmp(input, "env", 3) == 0
		&& (input[3] == ' ' || input[3] == '\0'))
		return (env(minishell));
	else if (ft_strncmp(input, "export", 6) == 0
		&& (input[6] == ' ' || input[6] == '\0'))
		return (export(minishell, input + 7));
	else if (ft_strncmp(input, "pwd", 3) == 0
		&& (input[3] == ' ' || input[3] == '\0'))
		return (pwd(input + 4));
	else if (ft_strncmp(input, "unset", 5) == 0
		&& (input[5] == ' ' || input[5] == '\0'))
		return (unset(minishell, input + 6));
	else
		return (127);
}
