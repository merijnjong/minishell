/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:05:46 by dkros             #+#    #+#             */
/*   Updated: 2024/12/20 18:12:48 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		if (array[i] != NULL)
			free(array[i]);
		i++;
	}
	free(array);
	return ;
}

void	cleanup_minishell(t_minishell *minishell)
{
	if (!minishell)
		return ;
	if (minishell->next_env != NULL)
	{
		free_envlist(minishell->next_env);
		minishell->next_env = NULL;
	}
	if (minishell->env != NULL)
	{
		free(minishell->env);
		minishell->env = NULL;
	}
	if (minishell->cmdlist.head != NULL)
	{
		free_commands(&minishell->cmdlist);
		minishell->cmdlist.head = NULL;
	}
	minishell->status = 0;
	rl_clear_history();
}

char	*get_environ_value(char *var_name, t_minishell *minishell)
{
	t_minishell	*current;
	size_t		len;
	char		*status_value;

	if (!minishell || !var_name)
		return (NULL);
	if (var_name[0] == '?' && var_name[1] == '\0')
	{
		status_value = ft_itoa(minishell->status);
		return (status_value);
	}
	len = ft_strlen(var_name);
	current = minishell->next_env;
	while (current)
	{
		if (ft_strncmp(current->env, var_name, len) == 0
			&& current->env[len] == '=')
			return (current->env + len + 1);
		current = current->next_env;
	}
	return (NULL);
}

char	*extract_var_name(char **src)
{
	char	*start;
	char	*var_name;
	size_t	var_len;

	(*src)++;
	start = *src;
	while (ft_isalnum(**src) || **src == '_' || **src == '?')
		(*src)++;
	var_len = *src - start;
	var_name = ft_strndup(start, var_len);
	return (var_name);
}

char	*handle_var(char **src, char *dst, t_minishell *minishell)
{
	int		len;
	char	*var_name;
	char	*value;
	int		is_question;

	var_name = extract_var_name(src);
	if (!var_name)
		return (NULL);
	value = get_environ_value(var_name, minishell);
	if (value == NULL || !*var_name)
	{
		free(var_name);
		return (NULL);
	}
	is_question = (*var_name == '?' && var_name[1] == '\0');
	ft_strcpy(dst, value);
	len = ft_strlen(value);
	if (is_question)
		free(value);
	free(var_name);
	return (dst + len);
}
