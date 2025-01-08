/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:41 by mjong             #+#    #+#             */
/*   Updated: 2025/01/08 12:52:46 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	remove_current_node(t_minishell **envlist, t_minishell *current,
	t_minishell *prev)
{
	if (prev != NULL)
		prev->next_env = current->next_env;
	else
		*envlist = current->next_env;
	free(current->env);
	free(current);
	return (0);
}

int	find_and_remove_node(t_minishell **envlist, char *target_var)
{
	t_minishell	*current;
	t_minishell	*prev;
	char		*current_var_name;
	int			i;

	prev = NULL;
	current = *envlist;
	while (current != NULL)
	{
		i = 0;
		current_var_name = get_var_name(current->env, &i);
		if (current_var_name && ft_strcmp(current_var_name, target_var) == 0)
		{
			free(current_var_name);
			remove_current_node(envlist, current, prev);
			return (1);
		}
		free(current_var_name);
		prev = current;
		current = current->next_env;
	}
	return (0);
}

void	process_unset_args(t_minishell **envlist, char **args)
{
	int	j;

	j = 1;
	while (args[j] != NULL)
	{
		find_and_remove_node(envlist, args[j]);
		j++;
	}
}

int	unset(t_minishell *envlist, char **args)
{
	if (args[1] == NULL)
		return (0);
	process_unset_args(&envlist, args);
	return (0);
}
