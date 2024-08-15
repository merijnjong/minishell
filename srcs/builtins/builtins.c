/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:21:25 by mjong             #+#    #+#             */
/*   Updated: 2024/08/07 16:25:07 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_check(char *input, t_status status)
{
	while (*input == ' ')
		input++;
	if (ft_strncmp(input, "cd", 2) == 0
		&& (input[2] == ' ' || input[2] == '\0'))
		return (cd(input + 3));
	else if (ft_strncmp(input, "echo", 4) == 0
		&& (input[4] == ' ' || input[4] == '\0'))
		return (echo(input + 5, status));
	else if (ft_strncmp(input, "env", 3) == 0
		&& (input[3] == ' ' || input[3] == '\0'))
		return (env());
	else if (ft_strncmp(input, "export", 6) == 0
		&& (input[6] == ' ' || input[6] == '\0'))
		return (export(input + 7));
	else if (ft_strncmp(input, "pwd", 3) == 0
		&& (input[3] == ' ' || input[3] == '\0'))
		return (pwd(input + 4));
	else if (ft_strncmp(input, "unset", 5) == 0
		&& (input[5] == ' ' || input[5] == '\0'))
		return (unset(input + 6));
	else
		return (127);
}
