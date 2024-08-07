/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:33 by mjong             #+#    #+#             */
/*   Updated: 2024/07/31 16:49:11 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char *input)
{
	char	percent;

	percent = '%';
	while (*input == 32)
		input++;
	if (ft_strncmp(input, "-n", 2) == 0)
	{
		if (input[3] == ' ' || input[3] == '\0')
			return (0);
		else
		{
			ft_printf("%s", input[2]);
			ft_printf("%c\n", percent);
		}
	}
	else
		ft_printf("%s\n", input);
	return (0);
}
