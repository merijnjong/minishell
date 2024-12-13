/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:05:55 by dkros             #+#    #+#             */
/*   Updated: 2024/12/13 10:34:28 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_between_quotes(char *str, int i)
{
	char	temp;
	int		j;

	temp = str[i];
	j = 1;
	i++;
	while (str[i] != '\0' && str[i] != temp)
	{
		j++;
		i++;
	}
	if (str[i] == '\0')
		return (-1);
	return (j);
}

int	ft_count_commands(char *str, char c)
{
	int	wordcount;
	int	i;

	wordcount = 1;
	i = 0;
	while (str[i] != '\0')
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

int	count_wordlen(char *str, int i)
{
	int	temp;
	int	len;

	len = 0;
	while (str[i] != '\0' && str[i] != '|')
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

int	is_in_quoted_section(char *str, int i)
{
	int	count;
	int	temp;

	count = 0;
	temp = i;
	while (str[temp--] != '\0')
	{
		if (str[temp] == 34 || str[temp] == 39)
			count++;
	}
	if (count % 2 == 1)
		return (1);
	return (0);
}
