/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:44:08 by mjong             #+#    #+#             */
/*   Updated: 2024/06/20 19:36:49 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input(void)
{
	char	*input;
	int		status;

	while (1)
	{
		input = readline("minishell> ");
		status = ft_parser(input);
		if (status == 1)
		{
			free(input);
			break;
		}
		if (input != NULL)
			add_history(input);
		free(input);
	}
	rl_clear_history();
}

int	main(int argc, char *envp[])
{
	envp = NULL;
	if (argc > 1)
		ft_input();
	else
		ft_printf("\033[31mError: Incorrect notation.\nStart program by typing: ./minishell start\e[0m\n");
	return (0);
}
