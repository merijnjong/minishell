/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:08:44 by mjong             #+#    #+#             */
/*   Updated: 2025/01/08 19:11:14 by dkros            ###   ########.fr       */
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

static int	add_init_env_node(t_minishell *current, char *env)
{
	t_minishell	*new_node;

	new_node = malloc(sizeof(t_minishell));
	if (new_node == NULL)
		return (1);
	new_node->env = ft_strdup(env);
	if (new_node->env == NULL)
	{
		free(new_node);
		return (1);
	}
	new_node->next_env = NULL;
	current->next_env = new_node;
	return (0);
}

static int	init_env_head(t_minishell *minishell, char **envp)
{
	minishell->env = ft_strdup(envp[0]);
	if (minishell->env == NULL)
	{
		free_envlist(minishell);
		return (1);
	}
	minishell->next_env = NULL;
	return (0);
}

static int	init_env_list(t_minishell *current, char **envp)
{
	int	i;

	i = 1;
	while (envp[i] != NULL)
	{
		if (add_init_env_node(current, envp[i]))
			return (1);
		current = current->next_env;
		i++;
	}
	return (0);
}

void	init_minishell(t_minishell *minishell, char **envp)
{
	minishell->status = 0;
	minishell->cmdlist.head = NULL;
	if (envp == NULL || envp[0] == NULL)
		return ;
	if (init_env_head(minishell, envp))
		return ;
	if (init_env_list(minishell, envp))
	{
		free_envlist(minishell);
		return ;
	}
}
