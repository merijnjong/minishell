/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:05:55 by dkros             #+#    #+#             */
/*   Updated: 2024/12/07 15:32:31 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_between_quotes(char *str, int i)
{
	int j;
	char temp;

	j = 1;
	temp = str[i];
	i++;
	while (str[i] && str[i] != temp)
	{
		j++;
		i++;
	}
	if (!str[i])
		return (-1);
	return (j);
}

int ft_count_commands(char *str, char c)
{
	int i;
	int wordcount;

	i = 0;
	wordcount = 1;
	while (str[i])
	{
		if (str[i] == c)
		{
			wordcount++;
			if (str[i + 1] != '\0' && str[i + 1] == c)
				return (-2);
		}
		if (str[i] == 34 || str[i] == 39)
		{
			if (count_between_quotes(str, i) < 0)
				return (-1);
			i += count_between_quotes(str, i);
		}
		i++;
	}
	return (wordcount);
}

int count_wordlen(char *str, int i)
{
	int len;
	int temp;

	len = 0;
	while (str[i] && str[i] != '|')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			temp = count_between_quotes(str, i);
			if (temp < 0)
				return (-1);
			i += temp;
			len += temp;
		}
		len++;
		i++;
	}
	return (len);
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

