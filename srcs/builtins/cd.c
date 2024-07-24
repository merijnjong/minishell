/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:28:25 by mjong             #+#    #+#             */
/*   Updated: 2024/07/24 18:24:07 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// still have to implement absolute paths

int cd(const char *cd_cmd)
{
	const char	*home;
	int			i;
	int			j;

	i = 0;
	while (cd_cmd[i] == 32)
		i++;
	j = ft_strlen(cd_cmd);
	if (cd_cmd == NULL || cd_cmd[0] == '\0' || i == j || strncmp(cd_cmd + i, "~", 1) == 0)
	{
		home = getenv("HOME");
		if (home != NULL)
			chdir(home);
		else
			ft_printf("cd: HOME environment variable not set\n");
	}
	else if (chdir(cd_cmd) == -1)
	{
		ft_printf("cd: not a directory: %s\n", cd_cmd);
		return (1);
	}
	return (0);
}
