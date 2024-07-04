/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:50:33 by mjong             #+#    #+#             */
/*   Updated: 2024/06/27 14:19:49 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser(char *input)
{
	if (input[0] == '\0')
		ft_printf("\033[31mERROR: Enter a command\e[0m\n");
	if (ft_strncmp(input, "exit", 5) == 0)
		return (1);

	return (0);
}
