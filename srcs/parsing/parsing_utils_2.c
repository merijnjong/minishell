/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:32:31 by mjong             #+#    #+#             */
/*   Updated: 2024/11/13 17:53:13 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_command(t_cmd *a)
{
	int	i;

	i = 0;
	if (a && a->filename)
		printf("filename: %s\n\n", a->filename);
	else
		return ;
	if (!a->args)
	{
		printf("\n");
		return ;
	}
	while (a->args[i])
	{
		printf("arg %i: %s\n", (i + 1), a->args[i]);
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
