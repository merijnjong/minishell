/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:52:12 by mjong             #+#    #+#             */
/*   Updated: 2024/12/20 16:15:28 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	ft_isdigit_str(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args, t_minishell *minishell)
{
	int	exit_status;

	exit_status = 0;
	if (args[1] != NULL)
	{
		if (args[2] != NULL)
		{
			ft_putstr_fd(" too many arguments\n", 2);
			return (1);
		}
		else if (!ft_isdigit_str(args[1]))
		{
			ft_putstr_fd(" numeric argument required\n", 2);
			return (2);
		}
		else
		{
			exit_status = ft_atoi(args[1]);
		}
	}
	ft_printf("exit\n");
	cleanup_minishell(minishell);
	exit(exit_status);
	return (0);
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
