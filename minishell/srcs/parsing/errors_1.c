/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:05:59 by dkros             #+#    #+#             */
/*   Updated: 2024/12/24 13:49:13 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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
	int	single_open;
	int	double_open;
	int	i;

	single_open = 0;
	double_open = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && double_open == 0)
			single_open = !single_open;
		else if (str[i] == '\"' && single_open == 0)
			double_open = !double_open;
		i++;
	}
	if (single_open)
		return (ft_fprintf(2, "syntax error near unexpected token '\''\n"), 1);
	if (double_open)
		return (ft_fprintf(2, "syntax error near unexpected token '\"'\n"), 1);
	return (0);
}
