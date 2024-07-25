/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:44:08 by mjong             #+#    #+#             */
/*   Updated: 2024/07/25 15:06:15 by mjong            ###   ########.fr       */
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
		if (ft_strncmp(input, "$?", 3) == 0)
			ft_printf("%d\n", status);
		// only works if its the first command made
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
			break ;
		}
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
