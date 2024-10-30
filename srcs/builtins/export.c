/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:37 by mjong             #+#    #+#             */
/*   Updated: 2024/10/30 17:17:16 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_node(t_envlist *last, char *var_name, char *var_value)
{
	t_envlist	*new_node;
	char		*new_env;
	char		*temp;

	new_node = (t_envlist *)malloc(sizeof(t_envlist));
	if (new_node == NULL)
		return ;
	temp = ft_strjoin(var_name, "=");
	new_env = ft_strjoin(temp, var_value);
	free(temp);
	new_node->env = new_env;
	new_node->next = NULL;
	if (last != NULL)
		last->next = new_node;
}

void	replace_env_node(t_envlist *current, char *var_name, char *var_value, char *env_name)
{
	char	*temp;

	free(current->env);
	temp = ft_strjoin(var_name, "=");
	current->env = ft_strjoin(temp, var_value);
	free(temp);
	free(env_name);
}

void	ft_setenv(char *var_name, char *var_value, t_envlist *envlist)
{
	t_envlist	*current;
	t_envlist	*last;
	char		*env_name;
	int			i;

	current = envlist;
	last = NULL;
	while (current != NULL)
	{
		i = 0;
		env_name = get_var_name(current->env, &i);
		if (env_name != NULL && strcmp(env_name, var_name) == 0)
		{
			replace_env_node(current, var_name, var_value, env_name);
			return ;
		}
		free(env_name);
		last = current;
		current = current->next;
	}
	add_env_node(last, var_name, var_value);
}

int	export(t_envlist *envlist, char *cmd)
{
	int		i;
	char	*env_struct;
	char	*var_name;
	char	*var_value;

	i = 0;
	env_struct = NULL;
	if (cmd[i + 1] == '\0')
		print_sorted_envlist(envlist);
	var_name = get_var_name(cmd, &i);
	if (var_name == NULL)
		return (1);
	var_value = get_var_value(cmd, i);
	ft_printf("var_value: %s\n", var_value);
	if (var_value == NULL)
	{
		ft_printf("work?\n"); // doesn't work
		free(var_name);
		return (1);
	}
	ft_setenv(var_name, var_value, envlist);
	free(var_name);
	free(var_value);
	return (0);
}
