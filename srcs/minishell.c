/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:44:08 by mjong             #+#    #+#             */
/*   Updated: 2024/08/07 14:57:43 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input(char *argv[], char *envp[])
{
	int		status;

	while (1)
	{
		argv[0] = readline("minishell> ");
		status = ft_parser(argv[0], envp);
		if (argv != NULL)
			add_history(argv[0]);
		free(argv[0]);
	}
	rl_clear_history();
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc == 1)
		ft_input(argv, envp);
	else
		ft_printf("\033[31mError: Incorrect notation.\n\
		Start program by typing: ./minishell\e[0m\n");
	return (0);
}
