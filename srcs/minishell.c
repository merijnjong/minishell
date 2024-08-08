/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:44:08 by mjong             #+#    #+#             */
/*   Updated: 2024/08/08 16:01:57 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_status *status)
{
	status->last = 0;
}

void	ft_input(char *argv[], char *envp[])
{
	t_status	status;

	init(&status);
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
			status.last = ft_parser(argv[0], envp, status);
			add_history(argv[0]);
		}
		else
			status.last = 130;
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
