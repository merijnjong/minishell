/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:56:10 by mjong             #+#    #+#             */
/*   Updated: 2024/11/14 12:47:56 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_commands(t_cmdlist *list)
{
	t_node	*current;
	char	**arg;

	current = list->head;
	while (current != NULL)
	{
        printf("Command: %s\n", current->cmd->filename);
        if (current->cmd->args)
		{
			arg = current->cmd->args;
            printf("Arguments: ");
            while (*arg != NULL)
			{
				printf("(%s) ", *arg);
				arg++;
			}
            printf("\n\n");
        }
        current = current->next;
    }
}

void	free_command(t_cmd *cmd)
{
	char	**arg;
	char	**env;

	arg = cmd->args;
	env = cmd->envp;
	if (cmd->filename) free(cmd->filename);
    if (cmd->args)
	{
        while (*arg != NULL)
		{
            free(*arg);
			arg++;
        }
        free(cmd->args);
    }
    if (cmd->envp)
	{
        while (*env != NULL)
		{
            free(*env);
			env++;
        }
        free(cmd->envp);
    }
    free(cmd);
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

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
	return ;
}

int	count_between_quotes(char *str, int i)
{
	char	temp;
	int		j;

	temp = str[i];
	j = 1;
	i++;
	while (str[i] && str[i] != temp)
	{
		j++;
		i++;
	}
	if (!str[i])
		return (-1);
	return (j);
}
