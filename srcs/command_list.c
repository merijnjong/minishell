/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:41:17 by mjong             #+#    #+#             */
/*   Updated: 2024/06/27 14:43:42 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	In dit bestand staan functies die een command list maken,
	Nodes toevoegen aan een command list,
	Commands toevoegen aan een node.
	Ook staan er functies in die de list recursief freed.
*/

void	add_node(t_node **head, char *input, char *output, char *executable)
{
	t_node	*new_node;
	t_node	*current_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->cmd = add_command(input, output, executable);
	if (!new_node->cmd)
	{
		free(new_node);
		return;
	}
	current_node = NULL;
	if (!*head)
		*head = new_node;
	else
	{
		current_node = *head;
		while (current_node->next != NULL)
			current_node = current_node->next;
		current_node->next = new_node;
	}
}

t_cmd	*add_command(char *input, char *output, char *executable)
{
	t_cmd	*command;

	command = (t_cmd *)malloc(sizeof(t_cmd *));
	if (!command)
		return (NULL);
	command->input = ft_strdup(input);
	if (!command->input)
		return (free(command), NULL);
	command->output = ft_strdup(output);
	if (!command->output)
	{
		free(input);
		return (free(command), NULL);
	}
	command->executable = ft_strdup(executable);
	if (!command->output)
	{
		free(output);
		free(input);
		return (free(command), NULL);
	}
	return (command);
}

t_cmdlist	*create_list(void)
{
	t_cmdlist	*list;

	list = malloc(sizeof(t_cmdlist));
	if (!list)
		return (free(list), NULL);
	list->head = NULL;
	return (list);
}

void free_command(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free(cmd->input);
	free(cmd->output);
	free(cmd->executable);
	free(cmd);
}

void free_cmdlist_recursive(t_node *node)
{
	if (!node)
		return ;
	free_cmdlist_recursive(node->next);
	free_command(node->cmd);
	free(node);
}

void free_cmdlist(t_cmdlist *list)
{
	if (!list)
		return ;
	free_cmdlist_recursive(list->head);
	free(list);
}
