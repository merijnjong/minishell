/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_uns_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:53:10 by mjong             #+#    #+#             */
/*   Updated: 2024/10/30 17:21:48 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	compare_strings(const void *a, const void *b)
{
	return (strcmp(*(const char **)a, *(const char **)b));
}

void	print_sorted_envlist(t_envlist *envlist)
{
	char	**env_array;
	int		size;
	int		i;

	i = 0;
	env_array = envlist_to_array(envlist, &size);
	if (env_array == NULL)
		return ;
	qsort(env_array, size, sizeof(char *), compare_strings);
	while (i < size)
	{
		ft_printf("%s\n", env_array[i]);
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

char	*get_var_value(char *cmd, int i)
{
	int		j;
	char	*var_value;

	j = 0;
	var_value = NULL;
	if (cmd[i] == ' ')
	{
		var_value = (char *)malloc(1);
		if (!var_value)
			return (NULL);
		var_value[0] = '\0';
		return (var_value);
	}
	while (cmd[i + j] != '\0')
		j++;
	var_value = (char *)malloc(sizeof(char) * (j + 1));
	if (var_value == NULL)
		return (NULL);
	strncpy(var_value, cmd + i, j);
	var_value[j] = '\0';
	return (var_value);
}

char	*get_var_name(char *cmd, int *i)
{
	int		j;
	char	*var_name;

	j = 0;
	while (cmd[*i] == ' ')
		(*i)++;
	while (cmd[*i + j] != '=' && cmd[*i + j] != '\0')
		j++;
	if (cmd[j - 1] == ' ')
	{
		ft_printf("zsh: %s not found\n", cmd);
		return (NULL);
	}
	var_name = (char *)malloc(sizeof(char) * (j + 1));
	if (var_name == NULL)
		return (NULL);
	ft_strncpy(var_name, cmd + *i, j);
	var_name[j] = '\0';
	*i += j + 1;
	return (var_name);
}
