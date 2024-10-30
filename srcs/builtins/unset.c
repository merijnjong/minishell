/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:41 by mjong             #+#    #+#             */
/*   Updated: 2024/10/30 17:07:05 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_current_node(t_envlist *envlist, t_envlist *current, t_envlist *prev)
{
	if (prev)
		prev->next = current->next;
	else
		envlist = current->next;
	free(current->env);
	free(current);
	return (0);
}

int	unset(t_envlist *envlist, char *var_name)
{
	t_envlist	*current;
	t_envlist	*prev;
	char		*current_var_name;
	int			i;

	current = envlist;
	prev = NULL;
	while (current)
	{
		i = 0;
		current_var_name = get_var_name(current->env, &i);
		if (current_var_name && strcmp(current_var_name, var_name) == 0)
		{
			free(current_var_name);
			return (remove_current_node(envlist, current, prev));
		}
		free(current_var_name);
		prev = current;
		current = current->next;
	}
	return (0);
}
