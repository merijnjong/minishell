/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:08:44 by mjong             #+#    #+#             */
/*   Updated: 2024/12/20 18:12:22 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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

int	init_envlist_head(t_minishell *envlist, char **envp, int i)
{
	if (envp[i] != NULL)
	{
		envlist->env = ft_strdup(envp[i]);
		if (envlist->env == NULL)
			return (1);
		envlist->next_env = NULL;
		return (0);
	}
	else
	{
		envlist->env = NULL;
		envlist->next_env = NULL;
		return (0);
	}
}

int	append_to_envlist(t_minishell *current, char **envp, int i)
{
	t_minishell	*new_node;

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
		current->next_env = new_node;
		current = new_node;
		i++;
	}
	return (0);
}

int	start_envlist(t_minishell *envlist, char **envp, int i)
{
	if (init_envlist_head(envlist, envp, i) != 0)
		return (1);
	if (envp[i] != NULL)
		return (append_to_envlist(envlist, envp, i + 1));
	return (0);
}
