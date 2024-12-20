/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:05:59 by dkros             #+#    #+#             */
/*   Updated: 2024/12/20 16:06:35 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_metachar(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	is_valid_double(char *str, int i)
{
	if (str[i] != '\0' && (str[i] == '<' || str[i] == '>'))
	{
		if (str[i - 1] != '\0' && str[i - 1] == str[i] && str[i - 2]
			&& is_metachar(str[i - 2]) == 0)
			return (1);
	}
	return (0);
}

char	get_first_metachar(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_metachar(str[i]))
			return (str[i]);
		i++;
	}
	return (0);
}

int	check_for_uneven_quotes(char *str)
{
	int	single_count;
	int	double_count;
	int	i;

	single_count = 0;
	double_count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34)
			double_count++;
		if (str[i] == 39)
			single_count++;
		i++;
	}
	if (single_count % 2 == 1)
		return (ft_printf("syntax error near unexpected token '\''\n"), 1);
	if (double_count % 2 == 1)
		return (ft_printf("syntax error near unexpected token '\"'\n"), 1);
	return (0);
}
