/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:56:07 by mjong             #+#    #+#             */
/*   Updated: 2024/12/20 16:00:05 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_prints(char *s)
{
	int	chars;

	chars = 0;
	if (!s)
	{
		return (write(1, "(null)", 6));
	}
	while (*s != '\0')
	{
		chars += ft_printc(*s);
		s++;
	}
	return (chars);
}
