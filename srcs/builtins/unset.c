/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:41 by mjong             #+#    #+#             */
/*   Updated: 2024/11/21 16:28:53 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_current_node(t_minishell **envlist, t_minishell *current, t_minishell *prev)
{
	if (prev != NULL)
		prev->next_env = current->next_env;
	else
		*envlist = current->next_env;
	free(current->env);
	free(current);
	return (0);
}

int	unset(t_minishell *envlist, char *var_name)
{
	t_minishell	*current;
	t_minishell	*prev;
	char		*current_var_name;
	int			i;

	current = envlist;
	prev = NULL;
	while (current != NULL)
	{
		i = 0;
		current_var_name = get_var_name(current->env, &i);
		if (current_var_name && ft_strcmp(current_var_name, var_name) == 0)
		{
			free(current_var_name);
			return (remove_current_node(&envlist, current, prev));
		}
		free(current_var_name);
		prev = current;
		current = current->next_env;
	}
	return (0);
}
