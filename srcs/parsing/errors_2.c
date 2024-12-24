/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:46:37 by mjong             #+#    #+#             */
/*   Updated: 2024/12/24 14:16:50 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_quote_states(char current_char, int *in_single_quote,
	int *in_double_quote)
{
	if (current_char == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	else if (current_char == '"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
}

static int	check_metachar_syntax(char *str, char *last_char)
{
	int	in_single_quote;
	int	in_double_quote;
	int	i;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;

	while (str[i] != '\0' && !ft_isspace(str[i]))
	{
		update_quote_states(str[i], &in_single_quote, &in_double_quote);
		if (!in_single_quote && !in_double_quote)
		{
			if (is_metachar(str[i]) && is_metachar(*last_char)
				&& !is_valid_double(str, i))
			{
				ft_fprintf(2, "syntax error near unexpected token '%c'\n",
					*last_char);
				return (*last_char);
			}
			*last_char = str[i];
		}
		i++;
	}
	return (i);
}

static int	check_for_quotes_or_trailing_metachar(char *str, char last_char)
{
	int	in_single_quote;
	int	in_double_quote;
	int	i;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	if (check_for_uneven_quotes(str) == 1)
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		last_char = str[i];
		i++;
	}
	if (is_metachar(last_char) && !in_single_quote && !in_double_quote)
	{
		ft_fprintf(2, "syntax error near unexpected token '%c'\n", last_char);
		return (last_char);
	}
	return (0);
}

int	check_for_errors(char *str)
{
	char	last_char;
	int		i;

	i = 0;
	if (str[i] == '\0')
		return (1);
	last_char = get_first_metachar(str);
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && ft_isspace(str[i]))
			i++;
		if (str[i] != '\0')
			i += check_metachar_syntax(&str[i], &last_char);
	}
	return (check_for_quotes_or_trailing_metachar(str, last_char));
}
