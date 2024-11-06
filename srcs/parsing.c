/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:22:14 by mjong             #+#    #+#             */
/*   Updated: 2024/11/06 18:22:44 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
