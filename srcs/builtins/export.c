/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:37 by mjong             #+#    #+#             */
/*   Updated: 2024/11/14 17:02:10 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_node(t_minishell *last, char *var_name, char *var_value)
{
	t_minishell	*new_node;
	char		*new_env;
	char		*temp;

	new_node = (t_minishell *)malloc(sizeof(t_minishell));
	if (new_node == NULL)
		return ;
	temp = ft_strjoin(var_name, "=");
	new_env = ft_strjoin(temp, var_value);
	free(temp);
	new_node->env = new_env;
	new_node->next_env = NULL;
	if (last != NULL)
		last->next_env = new_node;
}

void	replace_env_node(t_minishell *current, char *var_name, char *var_value, char *env_name)
{
	char	*temp;

	free(current->env);
	temp = ft_strjoin(var_name, "=");
	current->env = ft_strjoin(temp, var_value);
	free(temp);
	free(env_name);
}

void	ft_setenv(t_minishell *envlist, char *var_name, char *var_value)
{
	t_minishell	*current;
	t_minishell	*last;
	char		*env_name;
	int			i;

	current = envlist;
	last = NULL;
	while (current != NULL)
	{
		i = 0;
		env_name = get_var_name(current->env, &i);
		if (env_name != NULL && ft_strcmp(env_name, var_name) == 0)
		{
			replace_env_node(current, var_name, var_value, env_name);
			return ;
		}
		free(env_name);
		last = current;
		current = current->next_env;
	}
	add_env_node(last, var_name, var_value);
}

int check_var_name(char *var_name)
{
	int i;

	i = 0;
	if (!(ft_isalpha(var_name[0]) || var_name[0] == '_'))
	{
		ft_printf("minishell: export: '%s': not a valid identifier\n", var_name);
		return (1);
	}
	while (var_name[i])
	{
		if (!(ft_isalnum(var_name[i]) || var_name[i] == '_'))
		{
			ft_printf("minishell: export: '%s': not a valid identifier\n", var_name);
			return (1);
		}
		i++;
	}
	return (0);
}

int	export(t_minishell *envlist, char *cmd)
{
	int		i;
	char	*var_name;
	char	*var_value;

	i = 0;
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == '\0')
		return (print_sorted_envlist(envlist));
	var_name = get_var_name(cmd, &i);
	if (var_name == NULL || check_var_name(var_name) == 1)
		return (1);
	var_value = get_var_value(cmd, i);
	if (var_value == NULL)
	{
		free(var_name);
		return (1);
	}
	ft_setenv(envlist, var_name, var_value);
	free(var_name);
	free(var_value);
	return (0);
}
