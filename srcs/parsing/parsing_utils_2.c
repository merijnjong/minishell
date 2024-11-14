/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:32:31 by mjong             #+#    #+#             */
/*   Updated: 2024/11/14 17:16:03 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_command(t_minishell *a)
{
	int	i;

	i = 0;
	if (a && a->command)
		printf("filename: %s\n\n", a->command);
	else
		return ;
	if (!a->arguments)
	{
		printf("\n");
		return ;
	}
	while (a->arguments[i])
	{
		printf("arg %i: %s\n", (i + 1), a->arguments[i]);
		i++;
	}
	ft_printf("\n");
	ft_printf("\n");
	return ;
}

void	ft_print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
	return ;
}
