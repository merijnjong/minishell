/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokanization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:50:25 by mjong             #+#    #+#             */
/*   Updated: 2024/06/27 14:45:33 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int *ft_get_token(char *str, int i)
{
	str = NULL;
	i = 0;
	return (0);
}

t_tokenlist	*ft_tokenize(char *str)
{
	int		i;
	char	*delimiters;

	i = 0;
	delimiters = " \n\t";
	while (str[i] != '\0')
	{
		if (str[i] == '|' || str[i] == '>' ||str[i] == '<'
			|| str[i] == '"' || str[i] == 39 || str[i] == '$')
			ft_get_token(str, i);
	}
}
