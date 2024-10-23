/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:50:33 by mjong             #+#    #+#             */
/*   Updated: 2024/10/23 14:58:57 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser(char *argv, char **envp, t_status status, t_envlist *envlist)
{
	pid_t	pid;

	if (ft_strncmp(argv, "exit", 5) == 0)
		ft_exit(argv);
	status.last = builtin_check(argv, status, envlist);
	if (status.last != 127)
		return (status.last);

	// ///// for entering ( some="thing" ) in terminal ///// 
	// int i = 0;
	// while (!(argv[i] == 61 && argv[i + 1] == 34))
	// 	i++;
	// if (argv[i] == 61 && argv[i + 1] == 34)
	// 	return (export(argv));
	// /////////////////////////////////////////////////////

	pid = fork();
	if (pid == -1)
		ft_error("fork");
	else if (pid == 0)
		ft_execute(argv, envp);
	else
	{
		if (waitpid(pid, &status.last, 0) == -1)
			ft_error("waitpid");
		if (WIFEXITED(status.last))
			return (WEXITSTATUS(status.last));
		else
			return (-1);
	}
	return (0);
}

// typedef struct s_args
// {
// 	char *cmd;
// 	int type;
// 	struct s_args *next;
// } t_args;

// int8_t	is_redirection(char *input, size_t ndx)
// {
// 	if (ft_strncmp(&input[ndx], "<<", 2) == 0)
// 		return (2);
// 	if (ft_strncmp(&input[ndx], "<", 1) == 0)
// 		return (1);
// 	if (ft_strncmp(&input[ndx], ">>", 2) == 0)
// 		return (2);
// 	if (ft_strncmp(&input[ndx], ">", 1) == 0)
// 		return (1);
// 	return (0);
// }

// int8_t	add_redirection(t_cmd *cmd, char *input, size_t ndx, int8_t skip)
// {
// 	int new_ndx;
// 	input = &input[ndx + skip];
// 	input = skip_spaces(input);
// 	char *word = get_arg(input, &new_ndx);
// 	if (word == NULL)
// 		return (-1);
// 	if (add_to_cmd(word, cmd, ndx) == -1)
// 		return (free(word), -1);
// 	return (0);
// }

// int	add_to_cmd(t_cmd *cmd, char *input, size_t ndx)
// {
// 	int skip;

// 	skip = is_redirection(input, ndx);
// 	if (skip > 0)
// 		if (add_redirection(cmd, input, ndx, skip) == -1)
// 			return (-1);
// 	else if (is_pipe(input, ndx))
// 		if (add_pipe(cmd, input, ndx) == -1)
// 			return (-1);
// 	else
// 		if (add_word(cmd, input, ndx) == -1)
// 			return (-1);
// }

// int	parse_cmd(t_cmd *cmd, char *input, char	*envp[])
// {
// 	size_t	ndx;

// 	ndx = 0;
// 	while (input[ndx])
// 		if (add_to_cmd(input, ndx, cmd) == -1)
// 			return (-1);
// 	return (0);
// }

// int	ft_parser(char *input, char *envp[])
// {
// 	int exit_status;

// 	if (input[0] == '\0')
// 	{
// 		ft_printf("\033[31mERROR: Enter a command\e[0m\n");
// 		return (0);
// 	}
// 	t_cmd	cmd = {NULL, 0, NULL};
// 	if (parse_cmd(&cmd, input, envp) == -1)
// 	{
// 		ft_printf("Parse error\n");
// 		free_cmd(&cmd);
// 		return (1);
// 	}
// 	// if (replace_env_vars_and_quotes(&cmd, envp) == -1)
// 	// {
// 	// 	ft_printf("Replacing error\n");
// 	// 	free_cmd(&cmd);
// 	// 	return (1);
// 	// }
// 	exit_status = execute_cmd(&cmd, envp);
// 	free_cmd(&cmd);
// 	return (exit_status);
// 	// else if (ft_strncmp(input, "exit", 5) == 0)
// 	// {
// 	// 	ft_printf("exit\n");
// 	// 	return (1);
// 	// }
// 	// else if (ft_strncmp(input, "ls", 3) == 0)
// 	// 	ft_execute("/usr/bin/ls", envp);
// 	// else
// 	// 	return (builtincheck(input));
// 	// return (0);
// }