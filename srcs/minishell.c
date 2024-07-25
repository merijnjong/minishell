/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:44:08 by mjong             #+#    #+#             */
/*   Updated: 2024/07/25 17:34:47 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input(char *envp[])
{
	char	*input;
	int		status;

	while (1)
	{
		input = readline("minishell> ");
		status = ft_parser(input, envp);
		if (input != NULL)
			add_history(input);
		free(input);
	}
	rl_clear_history();
}

int	main(int argc, char *envp[])
{
	if (argc == 1)
		ft_input(envp);
	else
		ft_printf("\033[31mError: Incorrect notation.\n\
		Start program by typing: ./minishell\e[0m\n");
	return (0);
}
