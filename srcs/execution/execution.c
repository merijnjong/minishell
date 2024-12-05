/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:50:38 by mjong             #+#    #+#             */
/*   Updated: 2024/12/04 17:57:10 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_path_2(char **paths, char *cmd)
{
	int		i;
	char	*temp;
	char	*path;

	i = 0;
	while (paths[i] != NULL)
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*ft_find_path(char **envp, char *cmd)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (paths == NULL)
	{
		ft_free_dbl(paths);
		ft_error("paths");
	}
	path = ft_find_path_2(paths, cmd);
	ft_free_dbl(paths);
	return (path);
}

void	ft_execute(t_cmd *cmd, char **envp)
{
	char	*path;

	// Handle redirections if present
	if (cmd->redirect) {
		int fd;
		switch (cmd->redirect->type) {
			case REDIR_IN:
				fd = open(cmd->redirect->filename, O_RDONLY);
				if (fd == -1) {
					perror("Redirection");
					exit(1);
				}
				dup2(fd, STDIN_FILENO);
				close(fd);
				break;
			case REDIR_OUT:
				fd = open(cmd->redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd == -1) {
					perror("Redirection");
					exit(1);
				}
				dup2(fd, STDOUT_FILENO);
				close(fd);
				break;
			case REDIR_APPEND:
				fd = open(cmd->redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd == -1) {
					perror("Redirection");
					exit(1);
				}
				dup2(fd, STDOUT_FILENO);
				close(fd);
				break;
			case REDIR_HEREDOC:
				fprintf(stderr, "Heredoc not implemented\n");
				exit(1);
				break;
			default:
				break;
		}
	}
	path = ft_find_path(envp, cmd->filename);
	if (!path) {
		ft_printf("%s: command not found\n", cmd->filename);
		exit(127);
	}
	if (execve(path, cmd->args, envp) < 0)
		ft_error("execve");
}


// void ft_execute(char *argv, char **envp)
// {
//     char **cmd;
//     char *path;

//     // Split the command string into arguments
//     cmd = ft_split(argv, ' ');
//     if (!cmd || !cmd[0]) // Handle empty command case
//     {
//         ft_free_dbl(cmd);
//         ft_printf("minishell: empty command\n");
//         exit(127);
//     }

//     // Handle redirections (assuming this modifies cmd if necessary)
//     if (handle_redirects(cmd) != 0)
//     {
//         ft_free_dbl(cmd);
//         exit(1); // Exit with failure status for redirection error
//     }

//     // Find the executable path
//     path = ft_find_path(envp, cmd[0]);
//     if (!path) // If command not found in PATH
//     {
//         ft_free_dbl(cmd);
//         ft_printf("minishell: %s: command not found\n", cmd[0]);
//         exit(127); // Command not found exit code
//     }

//     // Attempt to execute the command
//     if (execve(path, cmd, envp) < 0) // If execve fails
//     {
//         ft_free_dbl(cmd);
//         free(path);
//         ft_error("execve"); // Provide a descriptive error
//         exit(126); // Execution failure exit code
//     }

//     // Cleanup (this point is unlikely to be reached because execve replaces the process)
//     ft_free_dbl(cmd);
//     free(path);
// }
