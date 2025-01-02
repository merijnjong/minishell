/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:47:01 by dkros             #+#    #+#             */
/*   Updated: 2025/01/02 17:51:36 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int is_matching_var(char *varname, char *to_compare)
{
	int len;

	len = ft_strlen(varname);
	if (ft_strncmp(varname, to_compare, len) == 0 &&
		to_compare[len] && to_compare[len] == '=')
			return (1);
	return (0);
}

char *get_new_env_str(char *var_to_change, char *new_value)
{
	int		i;
	char	*new_str;

	i = 0;
	while (var_to_change[i] && var_to_change[i] != '=')
		i++;
	new_str = malloc((i + ft_strlen(new_value) + 2) * sizeof(char));
	i = 0;
	while (var_to_change[i] && var_to_change[i] != '=')
	{
		new_str[i] = var_to_change[i];
		i++;
	}
	new_str[i] = '=';
	i++;
	while (*new_value != '\0')
		new_str[i++] = *new_value++;
	new_str[i] = '\0';
	return (new_str);
}

int update_env(t_minishell *env, char *var_to_change, char *value)
{
	t_minishell	*temp;
	char *test;
	char *new_str;

	temp = env;
	test = ft_strdup(value);
	while (temp != NULL)
	{
		if (is_matching_var(var_to_change, temp->env))
		{
			free(temp->env);
			new_str = get_new_env_str(var_to_change, test);
			free(test);
			temp->env = new_str;
			return (0);
		}
		temp = temp->next_env;
	}
	return (1);
}
