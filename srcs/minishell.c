/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:44:08 by mjong             #+#    #+#             */
/*   Updated: 2024/11/21 15:56:46 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_envlist(t_minishell *envlist, char **envp, int i)
{
	t_minishell	*new_node;

	while (envp[i])
	{
		new_node = malloc(sizeof(t_minishell));
		if (new_node == NULL)
			return ;
		new_node->env = ft_strdup(envp[i]);
		if (new_node->env == NULL)
		{
			free(new_node);
			return ;
		}
		new_node->next_env = NULL;
		envlist->next_env = new_node;
		envlist = new_node;
		i++;
	}
}

void	init(t_minishell *minishell, char **envp)
{
	t_minishell	*current;
	int			i;

	minishell->status = 0;
	current = minishell;
	i = 0;
	if (envp == NULL || envp[0] == NULL)
		return ;
	current->env = ft_strdup(envp[i]);
	if (current->env == NULL)
		return ;
	current->next_env = NULL;
	i++;
	start_envlist(current, envp, i);
}

// void	sigint_handler(int sig)
// {
// 	(void)sig;
// 	write(1, "\nminishell> ", 12);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// }

void	ft_input(char **argv, char **envp)
{
	t_minishell	minishell;
	t_cmdlist	cmdlist;

	init(&minishell, envp);
	// signal(SIGINT, sigint_handler);
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
			minishell.status = process(&minishell, &cmdlist, argv[0], envp);
			// minishell.status = parent_process(status, &envlist, argv[0], envp);
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
		ft_input(argv, envp);
	}
	else
		ft_printf("\033[31mError: Incorrect notation.\n\
		Start program by typing: ./minishell\e[0m\n");
	return (0);
}
