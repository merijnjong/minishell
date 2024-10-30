/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_uns_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:11:49 by mjong             #+#    #+#             */
/*   Updated: 2024/10/30 17:12:09 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envlist_count(t_envlist *envlist)
{
	int	count;

	count = 0;
	while (envlist)
	{
		count++;
		envlist = envlist->next;
	}
	return (count);
}
