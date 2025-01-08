/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:11:49 by mjong             #+#    #+#             */
/*   Updated: 2025/01/08 12:52:01 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	compare_strings(const char *a, const char *b)
{
	return (ft_strcmp(a, b));
}

int	envlist_count(t_minishell *envlist)
{
	int	count;

	count = 0;
	while (envlist != NULL)
	{
		count++;
		envlist = envlist->next_env;
	}
	return (count);
}

char	**envlist_to_array(t_minishell *envlist, int *size)
{
	t_minishell	*current;
	char		**array;
	int			count;
	int			i;

	count = envlist_count(envlist);
	i = 0;
	array = (char **)malloc(sizeof(char *) * (count + 1));
	if (array == NULL)
		return (NULL);
	current = envlist;
	while (i < count)
	{
		array[i] = ft_strdup(current->env);
		current = current->next_env;
		i++;
	}
	array[count] = NULL;
	*size = count;
	return (array);
}

int	print_sorted_envlist(t_minishell *envlist)
{
	char	**env_array;
	char	*equals_sign;
	int		size;
	int		i;

	i = -1;
	env_array = envlist_to_array(envlist, &size);
	if (env_array == NULL)
		return (1);
	ft_qsort(env_array, 0, size - 1, compare_strings);
	while (++i < size)
	{
		equals_sign = ft_strchr(env_array[i], '=');
		if (equals_sign != NULL)
		{
			*equals_sign = '\0';
			ft_printf("declare -x %s=\"%s\"\n", env_array[i], equals_sign + 1);
			*equals_sign = '=';
		}
		else
			ft_printf("declare -x %s\n", env_array[i]);
		free(env_array[i]);
	}
	free(env_array);
	return (0);
}

void	print_envlist(t_minishell *envlist)
{
	t_minishell	*current;

	current = envlist;
	while (current != NULL)
	{
		if (current->env != NULL)
			ft_printf("%s\n", current->env);
		current = current->next_env;
	}
}
