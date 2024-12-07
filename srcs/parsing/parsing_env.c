/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:06:01 by dkros             #+#    #+#             */
/*   Updated: 2024/12/07 16:42:00 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*get_environ_value(const char *var_name)
{
	int		i;
	size_t	len;

	i = 0;
	len = strlen(var_name);
	while (environ[i])
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
	while (isalnum(**src) || **src == '_')
		(*src)++;
	var_len = *src - start;
	var_name = strndup(start, var_len);
	if (!var_name)
		return (NULL);
	value = get_environ_value(var_name);
	if (!value || *value == '\0')
	{
		printf("minishell: invalid redirection: `$%s` is not defined\n", var_name);
		return (NULL);
	}
	free(var_name);
	strcpy(dst, value);
	return (dst + strlen(value));
}


char	*replace_vars(const char *str)
{
	char		*result;
	const char	*src;
	char		*dst;

	result = malloc(strlen(str) + 1);
	if (!result)
		return (NULL);
	src = str;
	dst = result;
	while (*src)
	{
		if (*src == '$' && *(src + 1) != '\0'
			&& (isalpha(*(src + 1)) || *(src + 1) == '_'))
		{
			char *new_dst = handle_var(&src, dst);
			if (!new_dst)
				return (free(result), NULL);
			dst = new_dst;
		}
		else
			*dst++ = *src++;
	}
	*dst = '\0';
	return (result);
}

