/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:00:08 by mjong             #+#    #+#             */
/*   Updated: 2024/11/13 17:50:29 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(t_cmd *cmd)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return NULL;
    new_node->cmd = cmd;
    new_node->next = NULL;
    return (new_node);
}

void	add_command(t_cmdlist *list, t_cmd *cmd)
{
	t_node	*new_node;
	t_node	*temp;

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

char	**array_dup(char **array)
{
	int		i;
	char	**duplicate_array;

	i = 0;
	while (array[i] != NULL)
		i++;
	duplicate_array = (char **)malloc((i + 1) * sizeof(char *));
	if (!duplicate_array)
		return (NULL);
	duplicate_array[i] = NULL;
	i--;
	while (i >= 0)
	{
		duplicate_array[i] = ft_strdup(array[i]);
		if (!duplicate_array[i])
		{
			while (duplicate_array[++i])
				free(duplicate_array[i]);
			free(duplicate_array);
			return (NULL);
		}
		i--;
	}
	return (duplicate_array);
}

t_cmd	*get_command(char **arg_array)
{
	t_cmd	*a;

	a = malloc(sizeof(t_cmd));
	a->filename = ft_strdup(arg_array[0]);
	if (!a->filename)
		return (free(a), NULL);
	a->args = array_dup(arg_array);
	if (!a->args)
	{
		free(a->filename);
		return (free(a), NULL);
	}
	a->envp = array_dup(environ);
	if (!a->envp)
	{
		free(a->filename);
		free_array(a->args);
		return (free(a), NULL);
	}
	return (a);
}
