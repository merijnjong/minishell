/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:46:37 by mjong             #+#    #+#             */
/*   Updated: 2024/12/19 12:54:47 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_metachar_syntax(char *str, char *last_char)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && !ft_isspace(str[i]))
	{
		if ((is_metachar(str[i]) && is_metachar(*last_char))
			&& !is_valid_double(str, i))
		{
			ft_printf("syntax error near unexpected token '%c'\n", *last_char);
			return (*last_char);
		}
		*last_char = str[i];
		i++;
	}
	return (i);
}

static int	check_for_quotes_or_trailing_metachar(char *str, char last_char)
{
	if (last_char == 0 || check_for_uneven_quotes(str) == 1)
		return (1);
	if (is_metachar(last_char))
	{
		ft_printf("syntax error near unexpected token '%c'\n", last_char);
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
