/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:39 by mjong             #+#    #+#             */
/*   Updated: 2024/12/20 16:14:19 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isprint2(char c)
{
	if (c >= 33 && c <= 126)
	{
		return (1);
	}
	return (0);
}

int	pwd(t_cmd *command)
{
	char	cwd[PATH_MAX];
	int		saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (handle_redirects(command) != 0)
		return (1);
	if (command->args[1] != NULL)
		return (ft_printf("pwd: too many arguments\n"));
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
		perror("getcwd");
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
    {
        close(saved_stdout);
        return (perror("Error restoring STDOUT"), 1);
    }
    close(saved_stdout);
	return (0);
}
