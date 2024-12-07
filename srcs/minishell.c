/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:44:08 by mjong             #+#    #+#             */
/*   Updated: 2024/12/07 16:22:34 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_envlist(t_minishell *head)
{
    t_minishell *tmp;

    while (head)
    {
        tmp = head->next_env;
        free(head->env);
        free(head);
        head = tmp;
    }
}

int start_envlist(t_minishell *envlist, char **envp, int i)
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

void	init(t_minishell *minishell, char **envp)
{
	t_minishell	*current;
	int			i;

	minishell->status = 0;
	minishell->cmdlist = NULL;
	i = 0;
	if (envp == NULL || envp[0] == NULL)
		return ;
	current = minishell;
	current->env = ft_strdup(envp[i]);
	if (current->env == NULL)
	{
		free_envlist(minishell);
		return ;
	}
	current->next_env = NULL;
	i++;
	if (start_envlist(current, envp, i) == 1)
	{
		free_envlist(minishell);
		minishell->env = NULL;
	}
}

void	ft_input(char **argv, char **envp)
{
	t_minishell	minishell;
	t_cmdlist	cmdlist;

	init(&minishell, envp);
	while (1)
	{
		argv[0] = readline("minishell> ");
		if (argv[0] == NULL)
		{
			ft_printf("exit\n");
			break ;
		}
		if (argv[0][0] != '\0')
		{
			cmdlist = ft_parsing(argv[0]);
			if (cmdlist.head == NULL)
				minishell.status = 1;
			minishell.status = process(&minishell, &cmdlist, envp);
			add_history(argv[0]);
		}
		else
			minishell.status = 130;
		free(argv[0]);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
	{
		setup_signals();
		ft_input(argv, envp);
	}
	else
		ft_printf("\033[31mError: Incorrect notation.\n\
		Start program by typing: ./minishell\e[0m\n");
	return (0);
}
