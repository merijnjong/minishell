/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:06:13 by dkros             #+#    #+#             */
/*   Updated: 2024/12/24 13:57:46 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_count_words(char *str, char c)
{
	int	wordcount;
	int	i;

	wordcount = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			while (str[i] != '\0' && str[i + 1 != '\0'] && str[i] != c)
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
		if (str[i] != '\0')
			i++;
	}
	return (wordcount);
}

int	ft_word_length(const char *s, char c, int start)
{
	char	quote_char;
	int		len;

	quote_char = 0;
	len = 0;
	while (s[start] && (s[start] != c || quote_char))
	{
		if ((s[start] == '\'' || s[start] == '\"') && !quote_char)
			quote_char = s[start];
		else if (s[start] == quote_char)
			quote_char = 0;
		len++;
		start++;
	}
	return (len);
}

void	remove_quotes(char *str)
{
	char	quote_char;
	int		i;
	int		j;

	quote_char = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !quote_char)
			quote_char = str[i];
		else if (str[i] == quote_char)
			quote_char = 0;
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

char	*extract_word_skip_quotes(char *s, char c, int *index)
{
	int		word_len;
	char	*word;

	while (s[*index] == c)
		(*index)++;
	word_len = ft_word_length(s, c, *index);
	if (word_len < 0)
		return (NULL);
	word = ft_substr(s, *index, word_len);
	if (!word)
		return (NULL);
	remove_quotes(word);
	*index += word_len;
	return (word);
}

char	**ft_split_skip_quotes(char *s, char c)
{
	char	**array;
	int		i;
	int		j;
	int		word_count;

	word_count = ft_count_words(s, c);
	if (word_count < 0)
		return (NULL);
	array = malloc((word_count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	j = 0;
	while (i < word_count)
	{
		array[i] = extract_word_skip_quotes(s, c, &j);
		if (!array[i])
		{
			free_array(array);
			return (NULL);
		}
		i++;
	}
	array[i] = NULL;
	return (array);
}
