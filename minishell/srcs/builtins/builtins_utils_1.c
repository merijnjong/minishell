/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:53:10 by mjong             #+#    #+#             */
/*   Updated: 2025/01/08 12:51:51 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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

char	*extract_and_update_var_name(char *cmd, int *i, int length)
{
	char	*var_name;

	var_name = (char *)malloc(sizeof(char) * (length + 1));
	if (var_name == NULL)
		return (NULL);
	ft_strncpy(var_name, cmd + *i, length);
	var_name[length] = '\0';
	if (cmd[*i + length] == '=')
		*i += length + 1;
	else
		*i += length;
	return (var_name);
}

int	validate_and_get_var_length(char *cmd, int i)
{
	int	j;

	j = 0;
	if (cmd[i] == '=')
	{
		ft_putstr_fd(" not a valid identifier", 2);
		return (-1);
	}
	while (cmd[i + j] != '=' && cmd[i + j] != '\0')
	{
		if (cmd[i + j] == ' ' && cmd[i + j + 1] != '='
			&& cmd[i + j + 1] != '\0')
		{
			ft_putstr_fd(" not a valid identifier", 2);
			return (-1);
		}
		j++;
	}
	return (j);
}

char	*get_var_name(char *cmd, int *i)
{
	int		length;
	char	*var_name;

	length = validate_and_get_var_length(cmd, *i);
	if (length == -1)
		return (NULL);
	var_name = extract_and_update_var_name(cmd, i, length);
	return (var_name);
}

// char	*get_var_name(char *cmd, int *i)
// {
// 	int		j;
// 	char	*var_name;

// 	j = 0;
// 	if (cmd[*i] == '=')
// 	{
// 		ft_printf("zsh: `%s` not found\n", cmd);
// 		return (NULL);
// 	}
// 	while (cmd[*i + j] != '=' && cmd[*i + j] != '\0')
// 	{
// 		if (cmd[*i + j] == ' ' && cmd[*i + j + 1] != '='
// 			&& cmd[*i + j + 1] != '\0')
// 		{
// 			ft_printf("zsh: %s not found\n", cmd);
// 			return (NULL);
// 		}
// 		j++;
// 	}
// 	var_name = (char *)malloc(sizeof(char) * (j + 1));
// 	if (var_name == NULL)
// 		return (NULL);
// 	ft_strncpy(var_name, cmd + *i, j);
// 	var_name[j] = '\0';
// 	*i += j + (cmd[*i + j] == '=' ? 1 : 0);
// 	return (var_name);
// }
