/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:06:05 by dkros             #+#    #+#             */
/*   Updated: 2024/12/20 16:06:11 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	get_meta_len(char *str, int i)
{
	if (str[i + 1] != '\0' && str[i + 1] == str[i])
		return (2);
	return (1);
}

int	new_strlen(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\0' && is_metachar(str[i]))
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
	int	meta_len;
	int	k;

	k = 0;
	if (*j > 0 && new_str[*j - 1] != ' ' && is_in_quoted_section(str, *i) == 0)
		new_str[(*j)++] = ' ';
	meta_len = get_meta_len(str, *i);
	while (k < meta_len)
	{
		new_str[(*j)++] = str[(*i)++];
		k++;
	}
	if (str[*i] != '\0' && str[*i] != ' '
		&& is_in_quoted_section(str, *i) == 0)
		new_str[(*j)++] = ' ';
}

char	*convert_string(char *str)
{
	char	*new_str;
	int		len;
	int		i;
	int		j;

	len = new_strlen(str);
	i = 0;
	j = 0;
	if (len < 0)
		return (NULL);
	new_str = malloc(len + 1);
	if (new_str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != '\0' && is_metachar(str[i]))
			add_spaces(new_str, str, &i, &j);
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}
