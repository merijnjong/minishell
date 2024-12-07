/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:06:01 by dkros             #+#    #+#             */
/*   Updated: 2024/12/07 17:35:11 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_environ_value(const char *var_name)
{
	size_t	len;
	int		i;

	len = strlen(var_name);
	i = 0;
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], var_name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*handle_var(const char **src, char *dst)
{
	const char	*start;
	char		*var_name;
	char		*value;
	size_t		var_len;

	(*src)++;
	start = *src;
	while (ft_isalnum(**src) || **src == '_')
		(*src)++;
	var_len = *src - start;
	var_name = ft_strndup(start, var_len);
	if (var_name == NULL)
		return (NULL);
	value = get_environ_value(var_name);
	if (value == NULL || *value == '\0')
	{
		ft_printf("minishell: invalid redirection: `$%s` is not defined\n", var_name);
		return (NULL);
	}
	free(var_name);
	ft_strcpy(dst, value);
	return (dst + ft_strlen(value));
}

char	*replace_vars(const char *str)
{
	const char	*src;
	char		*result;
	char		*dst;

	result = malloc(ft_strlen(str) + 1);
	if (result == NULL)
		return (NULL);
	src = str;
	dst = result;
	while (*src != '\0')
	{
		if (*src == '$' && *(src + 1) != '\0'
			&& (ft_isalpha(*(src + 1)) || *(src + 1) == '_'))
		{
			char *new_dst = handle_var(&src, dst);
			if (new_dst == NULL)
				return (free(result), NULL);
			dst = new_dst;
		}
		else
			*dst++ = *src++;
	}
	*dst = '\0';
	return (result);
}
