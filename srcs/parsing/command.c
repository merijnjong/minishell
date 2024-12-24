/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:06:07 by dkros             #+#    #+#             */
/*   Updated: 2024/12/24 13:49:38 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*get_command(char **arg_array)
{
	t_cmd	*cmd;
	char	**new_args;

	if (init_cmd_struct(&cmd) == 0)
		return (NULL);
	new_args = remove_redirections(arg_array, cmd->redirect);
	if (new_args == NULL)
	{
		free(cmd->redirect);
		free(cmd);
		return (NULL);
	}
	cmd->filename = ft_strdup(new_args[0]);
	if (cmd->filename == NULL)
	{
		free_array(new_args);
		free(cmd->redirect);
		free(cmd);
		return (NULL);
	}
	cmd->args = new_args;
	return (cmd);
}

char	**get_command_array(char *str)
{
	char	**command_array;
	int		wordcount;

	wordcount = ft_count_commands(str, '|');
	if (wordcount == -1)
		return (ft_fprintf(2, "Error: No ending quote\n"), NULL);
	if (wordcount == -2)
		return (ft_fprintf(2, "Error: Double pipes\n"), NULL);
	command_array = malloc((wordcount + 1) * sizeof(char *));
	if (command_array == NULL)
		return (ft_fprintf(2, "Error: Malloc fail\n"), NULL);
	command_array = fill_array(command_array, str, wordcount);
	if (command_array == NULL)
		return (NULL);
	return (command_array);
}

void	print_command(t_cmd *cmd)
{
	int	i;

	if (cmd == NULL)
		return ;
	ft_printf("Command: %s\n", cmd->filename);
	i = 0;
	if (cmd->args != NULL)
	{
		ft_printf("Arguments: ");
		while (cmd->args[i] != NULL)
			ft_printf("(%s) ", cmd->args[i++]);
		ft_printf("\n");
	}
	if (cmd->redirect != NULL)
	{
		ft_printf("Redirection: ");
		if (cmd->redirect->type == REDIR_IN)
			ft_printf("< %s\n", cmd->redirect->filename);
		else if (cmd->redirect->type == REDIR_OUT)
			ft_printf("> %s\n", cmd->redirect->filename);
		else if (cmd->redirect->type == REDIR_APPEND)
			ft_printf(">> %s\n", cmd->redirect->filename);
		else if (cmd->redirect->type == REDIR_HEREDOC)
			ft_printf("<< %s\n", cmd->redirect->filename);
		else
			ft_printf("none\n");
	}
	ft_printf("\n");
}

t_node	*create_node(t_cmd *cmd)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
		return (NULL);
	new_node->cmd = cmd;
	new_node->next = NULL;
	return (new_node);
}

void	free_command(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->filename != NULL)
	{
		free(cmd->filename);
		cmd->filename = NULL;
	}
	if (cmd->args != NULL)
	{
		free_array(cmd->args);
		cmd->args = NULL;
	}
	if (cmd->redirect != NULL)
	{
		if (cmd->redirect->filename != NULL)
		{
			free(cmd->redirect->filename);
			cmd->redirect->filename = NULL;
		}
		free(cmd->redirect);
		cmd->redirect = NULL;
	}
	free(cmd);
	cmd = NULL;
}
