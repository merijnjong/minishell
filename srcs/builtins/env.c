/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:28 by mjong             #+#    #+#             */
/*   Updated: 2024/12/20 15:10:28 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_minishell *envlist, t_cmd *command)
{
	int saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (handle_redirects(command) != 0)
		return (1);
	print_envlist(envlist);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
    {
        close(saved_stdout);
        return (perror("Error restoring STDOUT"), 1);
    }
    close(saved_stdout);
	return (0);
}
