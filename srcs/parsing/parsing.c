/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:07:39 by mjong             #+#    #+#             */
/*   Updated: 2024/11/21 15:16:07 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* char **arguments in structs needs to be appended and turned into char *arguments 
before being returned to execution */

t_cmdlist	ft_parsing(char *argv)
{
	t_cmdlist	command_list;
	char		**command_array;
	char		*converted_string;

	if (check_for_errors(argv) != 0)
        return (command_list.head = NULL, command_list);
    converted_string = convert_string(argv);
    if (!converted_string)
        return (command_list.head = NULL, command_list);
    command_array = get_command_array(converted_string);
    free(converted_string);
	command_array = get_command_array(argv);
	command_list = put_in_cmdlist(command_array);
	print_commands(&command_list);
	return (command_list);
	// free_commands(&command_list);
	// free_array(command_array);
}
