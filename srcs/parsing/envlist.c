/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:08:44 by mjong             #+#    #+#             */
/*   Updated: 2024/12/15 07:42:00 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envlist(t_minishell *head)
{
	t_minishell	*temp;

	while (head != NULL)
	{
		temp = head->next_env;
		free(head->env);
		free(head);
		head = temp;
	}
}

int	start_envlist(t_minishell *envlist, char **envp, int i)
{
	t_minishell	*new_node;
	t_minishell	*current;

	current = envlist;
	while (envp[i] != NULL)
	{
		new_node = malloc(sizeof(t_minishell));
		if (new_node == NULL)
		{
			free_envlist(current);
			return (1);
		}
		new_node->env = ft_strdup(envp[i]);
		if (new_node->env == NULL)
		{
			free(new_node);
			free_envlist(current);
			return (1);
		}
		new_node->next_env = NULL;
		envlist->next_env = new_node;
		envlist = new_node;
		i++;
	}
	return (0);
}
