/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:33 by mjong             #+#    #+#             */
/*   Updated: 2024/08/07 16:06:51 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char *input, t_status status)
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
	else if (ft_strncmp(input, "$?", 2) == 0)
		ft_printf("%d\n", status.last);
	else
		ft_printf("%s\n", input);
	return (0);
}
