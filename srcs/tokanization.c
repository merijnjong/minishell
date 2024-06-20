/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokanization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:50:25 by mjong             #+#    #+#             */
/*   Updated: 2024/06/20 20:27:37 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int *ft_get_token(char *str, int i)
{
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
			|| str[i] == '"' || str[i] == "'" || str[i] == '$')
			ft_get_token(str, i);
	}
}