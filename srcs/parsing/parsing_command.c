/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:06:07 by dkros             #+#    #+#             */
/*   Updated: 2024/12/07 15:32:07 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	init_cmd_struct(t_cmd **cmd)
{
	*cmd = malloc(sizeof(t_cmd));
	if (!*cmd)
		return (0);
	(*cmd)->redirect = init_redirect();
	if (!(*cmd)->redirect)
	{
		free(*cmd);
		return (0);
	}
	return (1);
}

t_cmd	*get_command(char **arg_array)
{
	t_cmd	*cmd;
	char	**new_args;

	if (!init_cmd_struct(&cmd))
		return (NULL);
	new_args = remove_redirections(arg_array, cmd->redirect);
	if (!new_args)
	{
		free(cmd->redirect);
		free(cmd);
		return (NULL);
	}
	cmd->filename = ft_strdup(new_args[0]);
	if (!cmd->filename)
	{
		free_array(new_args);
		free(cmd->redirect);
		free(cmd);
		return (NULL);
	}
	cmd->args = new_args;
	return (cmd);
}

char **get_command_array(char *str)
{
	int wordcount;
	char **command_array;

	wordcount = ft_count_commands(str, '|');
	if (wordcount == -1)
		return (printf("Error: No ending quote\n"), NULL);
	if (wordcount == -2)
		return (printf("Error: Double pipes\n"), NULL);
	command_array = malloc((wordcount + 1) * sizeof(char *));
	if (!command_array)
		return (printf("Error: Malloc fail"), NULL);
	fill_array(command_array, str, wordcount);
	return (command_array);
}

void print_command(t_cmd *cmd)
{
    int i;

    if (!cmd)
        return;
    printf("Command: %s\n", cmd->filename);
    i = 0;
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

t_node *create_node(t_cmd *cmd)
{
	t_node *new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return NULL;
    new_node->cmd = cmd;
    new_node->next = NULL;
    return (new_node);
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

