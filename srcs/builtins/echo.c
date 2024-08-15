/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:33 by mjong             #+#    #+#             */
/*   Updated: 2024/08/08 16:26:34 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char *input, t_status status)
{
	while (*input == 32)
		input++;
	if (ft_strncmp(input, "-n", 2) == 0)
		ft_printf("%s", input + 3);
	else if (ft_strncmp(input, "$?", 2) == 0)
		ft_printf("%d\n", status.last);
	else
		ft_printf("%s\n", input);
	return (0);
}

// int	echo(char *input, t_status status)
// {
// 	int	print_newline;

// 	print_newline = 1;
// 	while (*input == ' ')
// 		input++;
// 	if (strncmp(input, "-n", 2) == 0 && (input[2] == ' ' || input[2] == '\0'))
// 	{
// 		print_newline = 0;
// 		input += 2;
// 		while (*input == ' ')
// 			input++;
// 	}
// 	if (strncmp(input, "$?", 2) == 0 && (input[2] == ' ' || input[2] == '\0'))
//         printf("%d", status.last);
//     else
//         printf("%s", input);
//     if (print_newline)
//         printf("\n");
//     return (0);
// }
