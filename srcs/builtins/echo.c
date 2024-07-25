/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:33 by mjong             #+#    #+#             */
/*   Updated: 2024/07/25 17:29:22 by mjong            ###   ########.fr       */
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
		if (input[2] == ' ' || input[2] == '\0')
		{
			ft_printf("%s", input + 3);
			ft_printf("%c\n", percent);
		}
		else
			ft_printf("%s\n", input);
	}
	else
		ft_printf("%s\n", input);
	return (0);
}
