/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:06:13 by dkros             #+#    #+#             */
/*   Updated: 2024/12/07 15:06:14 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_count_words(char *str, char c)
{
	int i;
	int wordcount;

	i = 0;
	wordcount = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			while (str[i] && str[i + 1] && str[i] != c)
			{
				if (str[i] == 34 || str[i] == 39)
				{
					if (count_between_quotes(str, i) < 0)
						return (-1);
					i += count_between_quotes(str, i);
				}
				i++;
			}
			wordcount++;
		}
		if (str[i])
			i++;
	}
	return (wordcount);
}

int	ft_word_length(char *s, char c, int i)
{
	int	j;
	int temp;

	j = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		if (s[i] == 34 || s[i] == 39)
			{
				temp = count_between_quotes(s, i);
				if (temp < 0)
					return (-1);
				i += temp;
				j += temp;
			}
		i++;
		j++;
	}
	return (j);
}

char	**ft_split_skip_quotes(char*s, char c)
{
	int		i;
	int		j;
	char	**array;

	i = 0;
	j = 0;
	array = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!array || !s)
		return (NULL);
	while (i < ft_count_words(s, c))
	{
		while (s[j] == c)
			j++;
		array[i] = ft_substr(s, j, ft_word_length(s, c, j));
		if (array[i] == NULL)
		{
			free_array(array);
			return (NULL);
		}
		j += ft_word_length(s, c, j);
		i++;
	}
	array[i] = NULL;
	return (array);
}

