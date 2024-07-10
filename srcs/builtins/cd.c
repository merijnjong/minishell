/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:28:25 by mjong             #+#    #+#             */
/*   Updated: 2024/07/10 17:09:15 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cd(const char *cd_cmd)
{
	const char	*home;
	int			i;
	int			j;

	i = 0;
	while (cd_cmd[i] == 32)
		i++;
	j = ft_strlen(cd_cmd);
	if (cd_cmd == NULL || cd_cmd[0] == '\0' || i == j)
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
