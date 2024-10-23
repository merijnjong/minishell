/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:44:08 by mjong             #+#    #+#             */
/*   Updated: 2024/10/23 16:04:04 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_envlist(char **envp, int i, t_envlist *current)
{
	t_envlist	*new_node;

	while (envp[i])
    {
        new_node = malloc(sizeof(t_envlist));
        if (new_node == NULL)
            return;
        new_node->env = ft_strdup(envp[i]);
        if (new_node->env == NULL)
        {
            free(new_node);
            return;
        }
        new_node->next = NULL;
        current->next = new_node;
        current = new_node;
        i++;
    }
}

void	init(t_status *status, t_envlist *envlist, char **envp)
{
    t_envlist	*current;
    int			i;

    status->last = 0;
	current = envlist;
	i = 0;
    if (!envp || !envp[0])
        return;
    current->env = ft_strdup(envp[i]);
    if (current->env == NULL)
        return;
    current->next = NULL;
    i++;
    start_envlist(envp, i, current);
}

void	ft_input(char **argv, char **envp)
{
	t_status	status;
	t_envlist	envlist;

	init(&status, &envlist, envp);
	// print_envlist(&envlist);
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
			status.last = ft_parser(argv[0], envp, status, &envlist);
			add_history(argv[0]);
		}
		else
			status.last = 130;
		free(argv[0]);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		ft_input(argv, envp);
	else
		ft_printf("\033[31mError: Incorrect notation.\n\
		Start program by typing: ./minishell\e[0m\n");
	return (0);
}
