/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:37 by mjong             #+#    #+#             */
/*   Updated: 2024/10/23 17:56:03 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_var_value(char *cmd, int i)
{
	int		j;
	char	*var_value;

	j = 0;
	var_value = NULL;
	if (cmd[i] == ' ')
	{
		var_value = (char *)malloc(1);
        if (!var_value)
            return NULL;
        var_value[0] = '\0';
        return (var_value);
	}
	while (cmd[i + j] != '\0')
		j++;
	var_value = (char *)malloc(sizeof(char) * (j + 1));
	if (!var_value)
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
	if (!var_name)
		return (NULL);
	ft_strncpy(var_name, cmd + *i, j);
	var_name[j] = '\0';
	*i += j + 1;
	return (var_name);
}

void	ft_setenv(char *var_name, char *var_value, t_envlist *envlist)
{
    t_envlist	*current;
	char		*env_name;
	int			i;

	current = envlist;
    while (current != NULL)
    {
        i = 0;
        env_name = get_var_name(current->env, &i);
		// wrong comparison;
        if (env_name != NULL && strcmp(env_name, var_name) == 0)
        {
            free(current->env);
            current->env = (char *)malloc(ft_strlen(var_name) + ft_strlen(var_value) + 2);
            sprintf(current->env, "%s=%s", var_name, var_value);
            free(env_name);
            return ;
        }
        free(env_name);
        current = current->next;
    }
}

int	export(char *cmd, t_envlist *envlist)
{
	int		i;
	char	*env_struct;
	char	*var_name;
	char	*var_value;

	i = 0;
	env_struct = NULL;
	if (cmd[i + 1] == '\0')
		ft_printf("%s\n", env_struct);
	var_name = get_var_name(cmd, &i);
	if (!var_name)
		return (1);
	var_value = get_var_value(cmd, i);
	if (!var_value)
	{
		free(var_name);
		return (1);
	}
	ft_setenv(var_name, var_value, envlist);
	// setenv(var_name, var_value, 1); // need to make custom function
	free(var_name);
	free(var_value);
	return (0);
}
