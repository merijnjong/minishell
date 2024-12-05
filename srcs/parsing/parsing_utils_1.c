/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:56:10 by mjong             #+#    #+#             */
/*   Updated: 2024/12/04 18:21:17 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_command(t_cmd *cmd)
{
    if (!cmd)
        return;
    printf("Command: %s\n", cmd->filename);
    int i = 0;
    if (cmd->args)
    {
        printf("Arguments: ");
        while (cmd->args[i])
            printf("(%s) ", cmd->args[i++]);
        printf("\n");
    }
    if (cmd->redirect)
    {
        printf("Redirection: ");
        if (cmd->redirect->type == REDIR_IN)
            printf("< %s\n", cmd->redirect->filename);
        else if (cmd->redirect->type == REDIR_OUT)
            printf("> %s\n", cmd->redirect->filename);
        else if (cmd->redirect->type == REDIR_APPEND)
            printf(">> %s\n", cmd->redirect->filename);
        else if (cmd->redirect->type == REDIR_HEREDOC)
            printf("<< %s\n", cmd->redirect->filename);
        else
            printf("none\n");
    }
    printf("\n");
}

void free_command(t_cmd *cmd)
{
    if (!cmd)
        return;
    if (cmd->filename)
        free(cmd->filename);
    if (cmd->args)
        free_array(cmd->args);
    if (cmd->redirect)
    {
        if (cmd->redirect->filename)
            free(cmd->redirect->filename);
        free(cmd->redirect);
    }
    free(cmd);
}

void free_commands(t_cmdlist *list)
{
    t_node *current = list->head;
    t_node *next;
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
