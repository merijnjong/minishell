/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:53:10 by mjong             #+#    #+#             */
/*   Updated: 2024/10/31 14:22:37 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_strncpy(var_value, cmd + i, j);
	var_value[j] = '\0';
	return (var_value);
}

char	*get_var_name(char *cmd, int *i)
{
	int		j;
	char	*var_name;

	j = 0;
	if (cmd[*i] == '=')
	{
		ft_printf("zsh: `%s` not found\n", cmd);
		return (NULL);
	}
	while (cmd[*i + j] != '=' && cmd[*i + j] != '\0')
	{
		if (cmd[*i + j] == ' ' && cmd[*i + j + 1] != '=' && cmd[*i + j + 1] != '\0')
		{
			ft_printf("zsh: %s not found\n", cmd);
			return (NULL);
		}
		j++;
	}
	var_name = (char *)malloc(sizeof(char) * (j + 1));
	if (var_name == NULL)
		return (NULL);
	ft_strncpy(var_name, cmd + *i, j);
	var_name[j] = '\0';
	*i += j + (cmd[*i + j] == '=' ? 1 : 0);
	return (var_name);
}
