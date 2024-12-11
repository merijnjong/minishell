/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmdlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:06:10 by dkros             #+#    #+#             */
/*   Updated: 2024/12/11 15:10:53 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmdlist(t_cmdlist *list)
{
	list->head = NULL;
}

void	add_command(t_cmdlist *list, t_cmd *cmd)
{
	t_node	*new_node;
	t_node	*temp;

	new_node = create_node(cmd);
	if (new_node == NULL)
		return ;
	if (list->head == NULL)
		list->head = new_node;
	else
	{
		temp = list->head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

void	free_commands(t_cmdlist *list)
{
	t_node	*current;
	t_node	*next;

	current = list->head;
	while (current != NULL)
	{
		next = current->next;
		free_command(current->cmd);
		free(current);
		current = next;
	}
	list->head = NULL;
}

void	print_commands(t_cmdlist *list)
{
	t_node	*current;

	current = list->head;
	while (current != NULL)
	{
		print_command(current->cmd);
		current = current->next;
	}
}

t_cmdlist	put_in_cmdlist(char **command_array)
{
	t_cmdlist	command_list;
	t_cmd		*command;
	char		**temp;
	int			i;

	init_cmdlist(&command_list);
	i = 0;
	while (command_array[i] != NULL)
	{
		temp = ft_split_skip_quotes(command_array[i], ' ');
		if (temp == NULL)
			free_array(command_array);
		command = get_command(temp);
		if (command == NULL)
			free_array(command_array);
		add_command(&command_list, command);
		free_array(temp);
		i++;
	}
	return (command_list);
}
