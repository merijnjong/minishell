/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:52:12 by mjong             #+#    #+#             */
/*   Updated: 2024/10/30 17:13:05 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_exit(char *argv)
{
	free(argv);
	ft_printf("exit\n");
	exit(EXIT_SUCCESS);
}

void	ft_free_dbl(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	print_dbl_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		ft_printf("%s\n", ptr[i]);
		i++;
	}
}

void	print_envlist(t_envlist *envlist)
{
	t_envlist	*current;

	current = envlist;
	while (current != NULL)
	{
		if (current->env != NULL)
			ft_printf("%s\n", current->env);
		current = current->next;
	}
}
