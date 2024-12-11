/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:44:08 by mjong             #+#    #+#             */
/*   Updated: 2024/12/11 17:08:14 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input(char **argv, char **envp)
{
	t_minishell	minishell;
	t_cmdlist	cmdlist;

	init_minishell(&minishell, envp);
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
