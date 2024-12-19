/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:03:37 by mjong             #+#    #+#             */
/*   Updated: 2024/12/19 17:54:08 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*init_redirect(void)
{
	t_redirect	*redirect;

	redirect = malloc(sizeof(t_redirect));
	if (redirect == NULL)
		return (NULL);
	redirect->type = NO_REDIR;
	redirect->filename = NULL;
	return (redirect);
}

int	init_cmd_struct(t_cmd **cmd)
{
	*cmd = malloc(sizeof(t_cmd));
	if (*cmd == NULL)
		return (0);
	(*cmd)->redirect = init_redirect();
	if ((*cmd)->redirect == NULL)
	{
		free(*cmd);
		return (0);
	}
	return (1);
}

void	init_cmdlist(t_cmdlist *list)
{
	list->head = NULL;
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
