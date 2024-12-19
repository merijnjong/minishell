/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:44:08 by mjong             #+#    #+#             */
/*   Updated: 2024/12/19 13:03:24 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process_command(char **argv, t_minishell *minishell,
	t_cmdlist *cmdlist, char **envp)
{
	if (cmdlist->head != NULL)
	{
		minishell->status = process(minishell, cmdlist, envp);
		add_history(argv[0]);
	}
	free(argv[0]);
}

void	ft_handle_input(char **argv, t_minishell *minishell, t_cmdlist *cmdlist)
{
	argv[0] = readline("minishell> ");
	if (argv[0] == NULL)
	{
		ft_printf("exit\n");
		cleanup_minishell(minishell);
		exit(0);
	}
	if (argv[0][0] != '\0')
	{
		*cmdlist = ft_parsing(argv[0], minishell);
		if (cmdlist->head == NULL)
			minishell->status = 1;
	}
	else
		minishell->status = 130;
}

void	ft_input(char **argv, char **envp)
{
	t_minishell	minishell;
	t_cmdlist	cmdlist;

	init_minishell(&minishell, envp);
	while (1)
	{
		ft_handle_input(argv, &minishell, &cmdlist);
		ft_process_command(argv, &minishell, &cmdlist, envp);
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
