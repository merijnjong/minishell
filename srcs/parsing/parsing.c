/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:05:39 by dkros             #+#    #+#             */
/*   Updated: 2024/12/11 16:28:21 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdlist	ft_parsing(char *argv)
{
	t_cmdlist	command_list;
	char		**command_array;
	char		*converted_string;

	command_list.head = NULL;
	if (check_for_errors(argv) != 0)
		return (command_list);
	converted_string = convert_string(argv);
	if (converted_string == NULL)
		return (command_list);
	command_array = get_command_array(converted_string);
	free(converted_string);
	if (command_array == NULL)
		return (command_list);
	command_list = put_in_cmdlist(command_array);
	return (command_list);
}

void ft_print_array(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
	return ;
}

char	**fill_array(char **array, char *str, int wordcount)
{
	int	wordlen;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < wordcount && str[j] != '\0')
	{
		wordlen = count_wordlen(str, j);
		array[i] = ft_substr(str, j, wordlen);
		if (array[i] == NULL)
			return (clean_array(array, i), NULL);
		j += (wordlen + 1);
		i++;
	}
	array[wordcount] = NULL;
	return (array);
}

void	clean_array(char **array, int i)
{
	while (i--)
		free(array[i]);
	free(array);
}
