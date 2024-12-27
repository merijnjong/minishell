/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:44:08 by mjong             #+#    #+#             */
/*   Updated: 2024/12/27 16:07:50 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	handle_exit(t_minishell *minishell)
{
	ft_printf("exit\n");
	cleanup_minishell(minishell);
	exit(0);
}

static void	handle_command_line(t_minishell *minishell, char **argv,
	char **envp)
{
	if (minishell->cmdlist.head != NULL)
		free_commands(&minishell->cmdlist);
	minishell->cmdlist = ft_parsing(argv[0], minishell);
	if (minishell->cmdlist.head != NULL)
		minishell->status = process(minishell, envp);
	else
		minishell->status = 1;
	add_history(argv[0]);
}

static void	process_line(t_minishell *minishell, char **argv, char **envp)
{
	if (argv[0][0] != '\0' && !is_whitespace_only(argv[0]))
		handle_command_line(minishell, argv, envp);
	else
		minishell->status = 130;
	free(argv[0]);
}

void	ft_input(char **argv, char **envp)
{
	t_minishell	minishell;

	init_minishell(&minishell, envp);
	while (1)
	{
		argv[0] = readline("minishell> ");
		if (argv[0] == NULL)
			handle_exit(&minishell);
		process_line(&minishell, argv, envp);
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
