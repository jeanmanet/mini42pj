/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:26:17 by ory               #+#    #+#             */
/*   Updated: 2023/04/30 20:28:14 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_left_node(t_ast_node *left, int *pipe_fd, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork");
		global.exit_code = 1;
		return (-1);
	}
	else if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		if (left->type == AST_CMD)
			execute_cmd_node(left, data);
		else
			execute_pipe_node(left, data);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int	execute_right_node(t_ast_node *right, int *pipe_fd, t_data *data)
{
	int	returnval;

	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	returnval = execute_cmd_node(right, data);
	return (returnval);
}