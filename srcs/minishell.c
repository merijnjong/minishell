/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:44:08 by mjong             #+#    #+#             */
/*   Updated: 2024/06/20 17:40:17 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		ft_parser(input);
		if (input != NULL)
			add_history(input);
		free(input);
		// add clear_history function somewhere
	}
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
