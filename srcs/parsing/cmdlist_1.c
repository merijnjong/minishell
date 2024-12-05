/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:53:43 by mjong             #+#    #+#             */
/*   Updated: 2024/12/04 18:21:46 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_word_length(char *s, char c, int i)
{
	int	temp;
	int	j;

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

int	ft_count_words(char *str, char c)
{
	int	wordcount;
	int	i;

	wordcount = 0;
	i = 0;
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
		i++;
	}
	return (wordcount);
}

char	**ft_split_skip_quotes(char *s, char c)
{
	char	**array;
	int		i;
	int		j;

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

void init_cmdlist(t_cmdlist *list)
{
    list->head = NULL;
}

t_cmdlist put_in_cmdlist(char **command_array)
{
    int i;
    char **temp;
    t_cmd *command;
    t_cmdlist command_list;

    i = 0;
    init_cmdlist(&command_list);
    while (command_array[i])
    {
        temp = ft_split_skip_quotes(command_array[i], ' ');
        if (!temp)
            free_array(command_array);
        command = get_command(temp);
        if (!command)
            free_array(command_array);
        add_command(&command_list, command);
        free_array(temp);
        i++;
    }
    return (command_list);
}
