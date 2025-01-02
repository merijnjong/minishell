/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:06:10 by dkros             #+#    #+#             */
/*   Updated: 2024/12/27 16:41:22 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	add_command(t_cmdlist *list, t_cmd *cmd)
{
	t_node	*new_node;
	t_node	*temp;

	new_node = create_node(cmd);
	if (new_node == NULL)
	{
		free_command(cmd);
		return ;
	}
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

int	process_command(t_cmdlist *command_list, char *command_str)
{
	char	**temp;
	t_cmd	*command;

	temp = ft_split_skip_quotes(command_str, ' ');
	if (temp == NULL)
		return (0);
	command = get_command(temp);
	if (command == NULL)
	{
		free_array(temp);
		return (0);
	}
	add_command(command_list, command);
	free_array(temp);
	return (1);
}

t_cmdlist	put_in_cmdlist(char **command_array)
{
	int			i;
	t_cmdlist	command_list;

	init_cmdlist(&command_list);
	if (command_array == NULL)
		return (command_list);
	i = 0;
	while (command_array[i] != NULL)
	{
		if (!process_command(&command_list, command_array[i]))
		{
			free_array(command_array);
			free_commands(&command_list);
			return (command_list);
		}
		i++;
	}
	free_array(command_array);
	return (command_list);
}
