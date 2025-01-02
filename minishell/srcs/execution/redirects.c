/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:50:45 by mjong             #+#    #+#             */
/*   Updated: 2024/12/27 18:08:09 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	handle_heredoc_redirection(t_redirect *redirect)
{
	int	fd;

	fd = open(TMP_HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(redirect->filename), 1);
	if (write_to_heredoc_file(redirect, fd) != 0)
	{
		close(fd);
		return (1);
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

static int	handle_input_redirection(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_RDONLY);
	if (fd == -1)
		return (perror(redirect->filename), 1);
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
		return (perror(redirect->filename), 1);
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
		return (perror(redirect->filename), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
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
