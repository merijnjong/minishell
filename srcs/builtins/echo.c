/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:33 by mjong             #+#    #+#             */
/*   Updated: 2024/11/21 16:23:14 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_env(t_minishell *envlist, char *command)
{
	t_minishell	*current;
	char		*env;
	char		*env_name;
	int			i;

	command++;
	env = NULL;
	current = envlist;
	while (current != NULL)
	{
		i = 0;
		env_name = get_var_name(current->env, &i);
		if (ft_strcmp(env_name, command) == 0 && env_name != NULL)
		{
			env = current->env + i;
			free(env_name);
			break ;
		}
		free(env_name);
		current = current->next_env;
	}
	if (env == NULL)
		ft_printf("\n");
	else
		ft_printf("%s\n", env);
}

int	echo(t_minishell *minishell, char *command)
{
	if (ft_strcmp(command, "-n") == 0)
		ft_printf("%s", command + 3);
	else if (ft_strcmp(command, "$?") == 0)
		ft_printf("%d\n", minishell->status);
	else if (ft_strncmp(command, "$", 1) == 0)
		echo_env(minishell, command);
	else
		ft_printf("%s\n", command);
	return (0);
}
