/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:46:14 by mjong             #+#    #+#             */
/*   Updated: 2024/11/13 17:53:56 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_wordlen(char *str, int i)
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

char	**fill_array(char **array, char *str, int wordcount)
{
	int wordlen;
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < wordcount && str[j])
	{
		wordlen = count_wordlen(str, j);
		array[i] = ft_substr(str, j, wordlen);
		if (!array[i])
		{
			while (i--)
				free(array[i]);
			return (free(array), NULL);
		}
		j += (wordlen + 1);
		i++;
	}
	return (array);
}

int	ft_count_commands(char *str, char c)
{
	int wordcount;
	int i;

	wordcount = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			wordcount++;
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

char	**get_command_array(char *str)
{
	char	**command_array;
	int		wordcount;

	wordcount = ft_count_commands(str, '|');
	if (wordcount < 0)
		return (ft_printf("No ending quote"), NULL);
	command_array = malloc((wordcount + 1) * sizeof(char *));
	if (!command_array)
		return (ft_printf("Malloc fail"), NULL);
	command_array[wordcount] = NULL;
	fill_array(command_array, str, wordcount);
	return (command_array);
}
