/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:41:17 by mjong             #+#    #+#             */
/*   Updated: 2024/06/20 18:26:11 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node(t_node **head, char *input, char *output, char *executable)
{
	t_node	*new_node;
	t_node	*current_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node->prev = NULL;
	new_node->cmd = add_command(input, output, executable);
	new_node->next = NULL;
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

// create_list merijn
t_cmdlist	*create_list(void *data)
{
	t_cmdlist	*list;

	list = malloc(sizeof(t_cmdlist));
	if (!list)
		return (free(list), NULL);
	return (list);
}

// create_list devlin
t_cmdlist	create_list(t_cmdlist **list)
{
	t_node	*a;

	*list = (t_node *)malloc(sizeof(t_node));
	a = *list;
	if (!list)
		return ;
	cmd->top = NULL;
	a->size = 0;
	return ;
}
// ff naar kijken nog

void	free_list(t_cmdlist **list)
{
	t_cmdlist	*tempstack;
	t_node		*tempnode;

	tempstack = *list;
	if (tempstack->head == NULL)
	{
		free(tempstack);
		tempstack = NULL;
		return ;
	}
	tempnode = tempstack->head;
	while (tempnode->next != NULL)
	{
		tempnode = tempnode->next;
		free(tempnode->prev);
	}
	free(tempnode);
	tempnode = NULL;
	free(*list);
	list = NULL;
	return ;
}