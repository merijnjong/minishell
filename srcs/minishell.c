/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:44:08 by mjong             #+#    #+#             */
/*   Updated: 2024/12/19 14:31:56 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input(char **argv, char **envp)
{
	t_minishell	minishell;

	init_minishell(&minishell, envp);
	while (1)
	{
		argv[0] = readline("minishell> ");
		if (argv[0] == NULL)
		{
			ft_printf("exit\n");
			cleanup_minishell(&minishell);
			exit(0);
		}
		if (argv[0][0] != '\0')
		{
			minishell.cmdlist = ft_parsing(argv[0], &minishell);
			if (minishell.cmdlist.head != NULL)
			{
				minishell.status = process(&minishell, envp);
				free_commands(&minishell.cmdlist);
				minishell.cmdlist.head = NULL;
			}
			else
				minishell.status = 1;
			add_history(argv[0]);
		}
		else
			minishell.status = 130;
		free(argv[0]);
	}
	cleanup_minishell(&minishell);
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
