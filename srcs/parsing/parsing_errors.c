/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:05:59 by dkros             #+#    #+#             */
/*   Updated: 2024/12/07 15:06:00 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_metachar(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int is_valid_double(char *str, int i)
{
	if (str[i] && (str[i] == '<' || str[i] == '>'))
	{
		if (str[i - 1] && str[i - 1] == str[i] && str[i - 2]
			&& !is_metachar(str[i - 2]))
			return (1);
	}
	return (0);
}

char get_first_metachar(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (is_metachar(str[i]))
			return (str[i]);
		i++;
	}
	return (0);
}

int check_for_uneven_quotes(char *str)
{
	int i;
	int single_count;
	int double_count;

	i = 0;
	single_count = 0;
	double_count = 0;
	while (str[i])
	{
		if (str[i] == 34)
			double_count++;
		if (str[i] == 39)
			single_count++;
		i++;
	}
	if (single_count % 2 == 1)
		return (printf("syntax error near unexpected token '\''\n"), 1);
	if (double_count % 2 == 1)
		return (printf("syntax error near unexpected token '\"'\n"), 1);
	return (0);
}

int check_for_errors(char *str)
{
	int		i;
	char	last_char;

	i = 0;
	if (!str[i])
		return (1);
	last_char = get_first_metachar(str);
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		while (str[i] && !is_space(str[i]))
		{
			if ((is_metachar(str[i]) && is_metachar(last_char)) && !is_valid_double(str, i))
				return (printf("syntax error near unexpected token '%c'\n", last_char), last_char);
			last_char = str[i];
			i++;
		}
	}
	if (last_char == 0 || check_for_uneven_quotes(str) == 1)
		return (1);
	if (is_metachar(last_char))
		return (printf("syntax error near unexpected token '%c'\n", last_char), last_char);
	return (0);
}

