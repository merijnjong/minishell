/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:28:25 by mjong             #+#    #+#             */
/*   Updated: 2024/07/25 14:06:30 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_path(const char *cd_cmd, int i, int j)
{
	char	*path;
	
	path = ft_strndup(cd_cmd + i, j - i);
	if (chdir(path) == -1)
	{
		ft_printf("cd: not a directory: %s\n", path);
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

int	cd_home()
{
	const char	*home;

	home = getenv("HOME");
	if (home != NULL)
	{
		if (chdir(home) == -1)
		{
			ft_printf("cd: failed to change to home directory\n");
			return (1);
		}
	}
	else
	{
		ft_printf("cd: HOME environment variable not set\n");
		return (1);
	}
	return (0);
}

int cd(const char *cd_cmd)
{
	int	result;
	int	i;
	int	j;

	i = 0;
	while (cd_cmd[i] == 32)
		i++;
	j = ft_strlen(cd_cmd);
	while (j > i && cd_cmd[j - 1] == ' ')
        j--;
	if (i == j || (j - i == 1 && cd_cmd[i] == '~'))
		result = cd_home();
	else
		result = cd_path(cd_cmd, i, j);
	return (result);
}
