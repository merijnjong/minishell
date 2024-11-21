/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_dev.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:09:06 by mjong             #+#    #+#             */
/*   Updated: 2024/11/21 15:13:36 by mjong            ###   ########.fr       */
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

char check_for_errors(char *str)
{
	int		i;
	char	last_char;

	i = 0;
	if (!str[i])
		return (1);
	last_char = get_first_metachar(str);
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		while (str[i] && !ft_isspace(str[i]))
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

int	get_meta_len(char *str, int i)
{
	if (str[i + 1] && str[i + 1] == str[i])
		return (2);
	return (1);
}

int	new_strlen(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] && is_metachar(str[i]))
		{
			i += get_meta_len(str, i);
			count += 2;
		}
		else
			i++;
		count++;
	}
	return (count);
}

int is_in_quoted_section(char *str, int i)
{
	int temp;
	int count;

	temp = i;
	count = 0;
	while (str[temp--])
	{
		if (str[temp] == 34 || str[temp] == 39)
			count++;
	}
	if (count % 2 == 1)
		return (1);
	return (0);
}

void	add_spaces(char *new_str, char *str, int *i, int *j)
{
	int	k;
	int	meta_len;

	k = 0;
	if (*j > 0 && new_str[*j - 1] != ' ' && !is_in_quoted_section(str, *i))
		new_str[(*j)++] = ' ';
	meta_len = get_meta_len(str, *i);
	while (k < meta_len)
	{
		new_str[(*j)++] = str[(*i)++];
		k++;
	}
	if (str[*i] && str[*i] != ' '  && !is_in_quoted_section(str, *i))
		new_str[(*j)++] = ' ';
}

char	*convert_string(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = 0;
	j = 0;
	len = new_strlen(str);
	if (len < 0)
		return (NULL);
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] && is_metachar(str[i]))
			add_spaces(new_str, str, &i, &j);
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}
