/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:11:49 by mjong             #+#    #+#             */
/*   Updated: 2024/10/31 15:24:29 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_strings(const char *a, const char *b)
{
	return (ft_strcmp(a, b));
}

int	envlist_count(t_envlist *envlist)
{
	int	count;

	count = 0;
	while (envlist != NULL)
	{
		count++;
		envlist = envlist->next;
	}
	return (count);
}

char	**envlist_to_array(t_envlist *envlist, int *size)
{
	t_envlist	*current;
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
		current = current->next;
		i++;
	}
	array[count] = NULL;
	*size = count;
	return (array);
}

int	print_sorted_envlist(t_envlist *envlist)
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

void	print_envlist(t_envlist *envlist)
{
	t_envlist	*current;

	current = envlist;
	while (current != NULL)
	{
		if (current->env != NULL)
			ft_printf("%s\n", current->env);
		current = current->next;
	}
}
