/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_convert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:06:05 by dkros             #+#    #+#             */
/*   Updated: 2024/12/07 15:12:40 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

