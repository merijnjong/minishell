/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:44:08 by mjong             #+#    #+#             */
/*   Updated: 2024/10/09 16:51:22 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void init(t_status *status, t_envlist *envlist)
{
    char		**env;
    t_envlist	*current;

    status->last = 0;
    env = environ;
    current = envlist;
    while (*env)
    {
        current->env = strdup(*env);
        current->next = malloc(sizeof(t_envlist));
        current = current->next;
        current->env = NULL;
        current->next = NULL;
        env++;
    }
}

void	ft_input(char **argv, char **envp)
{
	t_status	status;
	t_envlist	envlist;

	init(&status, &envlist);
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
			status.last = ft_parser(argv[0], envp, status, envlist);
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
