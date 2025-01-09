/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:05:39 by dkros             #+#    #+#             */
/*   Updated: 2025/01/09 13:27:02 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*process_src(t_minishell *minishell, char *src, char *str, char *result)
{
	int		i;
	char	*dst;
	char	*new_dst;

	dst = result;
	while (*src)
	{
		i = src - str;
		if (*src == '$' && *(src + 1) != '\0' && is_in_quoted_section(str,
				i) != SINGLE_QUOTE && (ft_isalpha(*(src + 1))
				|| *(src + 1) == '_' || *(src + 1) == '?'))
		{
			new_dst = handle_var(&src, dst, minishell);
			if (new_dst == NULL)
			{
				free(result);
				return (NULL);
			}
			dst = new_dst;
		}
		else
			*dst++ = *src++;
	}
	*dst = '\0';
	return (result);
}

char	*replace_vars(t_minishell *minishell, char *str)
{
	char	*result;

	result = malloc((ft_strlen(str) * 4) + 1);
	if (!result)
	{
		free(str);
		return (NULL);
	}
	result = process_src(minishell, str, str, result);
	if (!result)
	{
		free(str);
		return (NULL);
	}
	free(str);
	return (result);
}

t_cmdlist	ft_parsing(char *argv, t_minishell *minishell)
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
	converted_string = replace_vars(minishell, converted_string);
	if (converted_string == NULL)
		return (command_list);
	command_array = get_command_array(converted_string);
	free(converted_string);
	if (command_array == NULL)
		return (command_list);
	command_list = put_in_cmdlist(command_array);
	if (command_list.head == NULL)
		ft_fprintf(2, "Error: Failed to process commands.\n");
	return (command_list);
}

void	ft_print_array(char **array)
{
	int	i;

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
