/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:19 by dkros             #+#    #+#             */
/*   Updated: 2025/01/08 15:30:55 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	update_quote_states(char c, int *single_quote, int *double_qoute)
{
	if (c == '\'' && !(*double_qoute))
		*single_quote = !(*single_quote);
	else if (c == '"' && !(*single_quote))
		*double_qoute = !(*double_qoute);
}

static int	scan_until_space_or_error(char *str, char *last_metachar)
{
	int	i;
	int	in_single_quote;
	int	in_double_qoute;

	i = 0;
	in_single_quote = 0;
	in_double_qoute = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		update_quote_states(str[i], &in_single_quote, &in_double_qoute);
		if (!in_single_quote && !in_double_qoute)
		{
			if (is_metachar(str[i]) && is_metachar(*last_metachar)
				&& !is_valid_double(str, i))
			{
				ft_fprintf(2, "syntax error near unexpected token '%c'\n",
					*last_metachar);
				return (-1);
			}
			*last_metachar = str[i];
		}
		i++;
	}
	return (i);
}

static int	check_trailing_metachar_and_quotes(char *str)
{
	int		i;
	int		in_single_quote;
	int		in_double_quote;
	char	last_char;

	if (check_for_uneven_quotes(str) == 1)
		return (1);
	in_single_quote = 0;
	in_double_quote = 0;
	i = -1;
	last_char = '\0';
	while (str[++i])
	{
		update_quote_states(str[i], &in_single_quote, &in_double_quote);
		last_char = str[i];
	}
	if (is_metachar(last_char) && !in_single_quote && !in_double_quote)
	{
		ft_fprintf(2, "syntax error near unexpected token '%c'\n", last_char);
		return (1);
	}
	return (0);
}

int	check_for_errors(char *str)
{
	int		i;
	int		scanned;
	char	last_metachar;

	if (!str || !str[0])
		return (1);
	if (check_trailing_metachar_and_quotes(str) == 1)
		return (1);
	i = 0;
	last_metachar = get_first_metachar(str);
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (!str[i])
			break ;
		scanned = scan_until_space_or_error(&str[i], &last_metachar);
		if (scanned < 0)
			return (1);
		i += scanned;
	}
	return (0);
}
