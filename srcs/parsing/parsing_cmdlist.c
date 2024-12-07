/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmdlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:06:10 by dkros             #+#    #+#             */
/*   Updated: 2024/12/07 15:31:49 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void init_cmdlist(t_cmdlist *list)
{
    list->head = NULL;
}


void add_command(t_cmdlist *list, t_cmd *cmd)
{
	t_node *new_node;
	t_node *temp;
	new_node = create_node(cmd);
	if (!new_node)
		return;
    if (!list->head)
        list->head = new_node;
    else
	{
        temp = list->head;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
}


void free_commands(t_cmdlist *list)
{
    t_node *current = list->head;
    t_node *next;
    while (current != NULL) {
        next = current->next;
        free_command(current->cmd);
        free(current);
        current = next;
    }
    list->head = NULL;
}


void print_commands(t_cmdlist *list)
{
	t_node *current;

	current = list->head;
	while (current != NULL)
	{
        print_command(current->cmd);
        current = current->next;
    }
}


t_cmdlist put_in_cmdlist(char **command_array)
{
	int i;
	char **temp;
	t_cmd *command;
	t_cmdlist command_list;

	i = 0;
	init_cmdlist(&command_list);
	while (command_array[i])
	{
		temp = ft_split_skip_quotes(command_array[i], ' ');
		if (!temp)
			free_array(command_array);
		command = get_command(temp);
		if (!command)
			free_array(command_array);
		add_command(&command_list, command);
		free_array(temp);
		i++;
	}
	return (command_list);
}

