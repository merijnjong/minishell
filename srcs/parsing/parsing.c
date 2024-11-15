/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:07:39 by mjong             #+#    #+#             */
/*   Updated: 2024/11/15 12:31:50 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdlist	ft_parsing(char *argv)
{
	t_cmdlist	command_list;
	char		**command_array;
	
	command_array = get_command_array(argv);
	command_list = put_in_cmdlist(command_array);
	print_commands(&command_list);
	return (command_list);
	// free_commands(&command_list);
	// free_array(command_array);
}
