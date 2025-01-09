/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:44:08 by mjong             #+#    #+#             */
/*   Updated: 2025/01/09 11:59:38 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	handle_exit(t_minishell *minishell)
{
	ft_printf("exit\n");
	cleanup_minishell(minishell);
	exit(0);
}

static void	handle_command_line(t_minishell *minishell, char **argv)
{
	if (minishell->cmdlist.head != NULL)
		free_commands(&minishell->cmdlist);
	minishell->cmdlist = ft_parsing(argv[0], minishell);
	if (minishell->cmdlist.head != NULL)
		minishell->status = process(minishell);
	else
		minishell->status = 1;
	add_history(argv[0]);
}

static void	process_line(t_minishell *minishell, char **argv)
{
	int	exit_code;

	if (ft_strcmp(argv[0], "exit") == 0)
	{
		exit_code = ft_exit(argv, minishell);
		if (exit_code != 0)
			minishell->status = exit_code;
		return ;
	}
	if (argv[0][0] != '\0' && !is_whitespace_only(argv[0]))
		handle_command_line(minishell, argv);
	else
		minishell->status = 130;
	free(argv[0]);
}

void	ft_input(char **argv, char **envp)
{
	t_minishell	minishell;

	init_minishell(&minishell, envp);
	if (update_shlvl(&minishell) == 1)
		ft_setenv(&minishell, "SHLVL", "1");
	while (1)
	{
		argv[0] = readline("minishell> ");
		if (argv[0] == NULL)
			handle_exit(&minishell);
		if (argv[0][0] != '\0')
			process_line(&minishell, argv);
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
		ft_fprintf(2, "\033[31mError: Incorrect notation.\n\
		Start program by typing: ./minishell\e[0m\n");
	return (0);
}
