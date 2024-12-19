/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:50:45 by mjong             #+#    #+#             */
/*   Updated: 2024/12/19 01:43:34 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_input_redirection(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_RDONLY);
	if (fd == -1)
		return (perror("Error opening file"), 1);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	handle_output_redirection(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("Error opening file"), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	handle_append_redirection(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("Error opening file"), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	handle_heredoc_redirection(t_redirect *redirect)
{
	int		fd;
	char	*line;

	fd = open(TMP_HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("Error creating heredoc file"), 1);
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, redirect->filename) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	fd = open(TMP_HEREDOC_FILE, O_RDONLY);
	if (fd == -1)
		return (perror("Error opening heredoc file"), 1);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_redirects(t_cmd *cmd)
{
	if (!cmd || !cmd->redirect)
		return (0);
	printf("{%s}", cmd->redirect->filename);
	if (cmd->redirect->type != NO_REDIR && !*cmd->redirect->filename)
		return (ft_printf("minishell: no such file or directory:\n"), 0);
	if (cmd->redirect->type == REDIR_IN)
		return (handle_input_redirection(cmd->redirect));
	else if (cmd->redirect->type == REDIR_OUT)
		return (handle_output_redirection(cmd->redirect));
	else if (cmd->redirect->type == REDIR_APPEND)
		return (handle_append_redirection(cmd->redirect));
	else if (cmd->redirect->type == REDIR_HEREDOC)
		return (handle_heredoc_redirection(cmd->redirect));
	return (0);
}
