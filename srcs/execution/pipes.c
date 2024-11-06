/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:38:52 by mjong             #+#    #+#             */
/*   Updated: 2024/11/06 16:21:53 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_array_len(char **cmds)
{
	int	i;

	i = 0;
	// print_dbl_ptr(cmds);
	while (cmds[i] != NULL)
	{
		i++;
	}
	// printf("i: %i\n", i);
	return (i);
}

pid_t	ft_execute_command(char *cmd, char *envp[], int input_fd, int output_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error("fork");
	if (pid == 0)
	{
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (output_fd != STDOUT_FILENO)
		{
			dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
		}
		ft_execute(cmd, envp);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int ft_execute_pipe(char *argv[], char *envp[], int cmd_count)
{
	int		input_fd;
	int		fd[2];
	int		i;
	pid_t	pid;

	input_fd = STDIN_FILENO;
	i = -1;
	while (++i < cmd_count)
	{
		if (i < cmd_count - 1)
		{
			if (pipe(fd) == -1)
				ft_error("pipe");
		}
		else
			fd[1] = STDOUT_FILENO;
		pid = ft_execute_command(argv[i], envp, input_fd, fd[1]);
		if (i < cmd_count - 1)
			close(fd[1]);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		input_fd = fd[0];
	}
    waitpid(pid, NULL, 0);
    return (0);
}

int	ft_call_pipe(t_status status, char *argv, char **envp)
{
	char	**cmds;

	cmds = ft_split(argv, '|');
	if (cmds == NULL)
	{
		ft_error("Memory allocation error");
		return (1);
	}
	status.last = ft_execute_pipe(cmds, envp, ft_array_len(cmds));
	ft_free_dbl(cmds);
	return (status.last);
}

// pid_t	ft_execute_command(char *cmd, char *envp[], int input_fd, int output_fd)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		ft_error("fork");
// 	if (pid == 0)
// 	{
// 		if (input_fd != STDIN_FILENO)
// 		{
// 			dup2(input_fd, STDIN_FILENO);
// 			close(input_fd);
// 		}
// 		if (output_fd != STDOUT_FILENO)
// 		{
// 			dup2(output_fd, STDOUT_FILENO);
// 			close(output_fd);
// 		}
// 		ft_execute(cmd, envp);
// 		exit(EXIT_FAILURE);
// 	}
// 	return (pid);
// }

// int	ft_execute_pipe(char *argv[], char *envp[], int cmd_count)
// {
//     int		i;
//     int		fd[2];
//     int		input_fd;
//     pid_t	pid;

// 	i = 0;
// 	input_fd = STDIN_FILENO;
//     while (i < cmd_count)
//     {
//         if (i < cmd_count - 1)
//         {
//             if (pipe(fd) == -1)
//             {
//                 ft_error("pipe");
//                 return (1);
//             }
//         }
//         else
//             fd[1] = STDOUT_FILENO;
//         pid = ft_execute_command(argv[i], envp, input_fd, fd[1]);
//         if (i < cmd_count - 1)
//             close(fd[1]);
//         if (input_fd != STDIN_FILENO)
//             close(input_fd);
//         input_fd = fd[0];
// 		i++;
//     }
//     waitpid(pid, NULL, 0);
//     return (0);
// }
