/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:03:37 by mjong             #+#    #+#             */
/*   Updated: 2024/12/20 18:18:54 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*init_redirect(void)
{
	t_redirect	*redirect;

	redirect = malloc(sizeof(t_redirect));
	if (redirect == NULL)
		return (NULL);
	redirect->type = NO_REDIR;
	redirect->filename = NULL;
	return (redirect);
}

int	init_cmd_struct(t_cmd **cmd)
{
	*cmd = malloc(sizeof(t_cmd));
	if (*cmd == NULL)
		return (0);
	(*cmd)->redirect = init_redirect();
	if ((*cmd)->redirect == NULL)
	{
		free(*cmd);
		return (0);
	}
	return (1);
}

void	init_cmdlist(t_cmdlist *list)
{
	list->head = NULL;
}
