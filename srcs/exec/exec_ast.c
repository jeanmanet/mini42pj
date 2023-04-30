/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:05:35 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/30 21:10:24 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_cmd_node(t_ast_node *node, t_data *data)
{
	int	returnval;

	returnval = exec_command(node->content->cmd, data);
	return (returnval);
}

int	execute_pipe_node(t_ast_node *node, t_data *data)
{
    	int	pipe_fd[2];
    	int	ret;
	pid_t	pid2;

    	if (pipe(pipe_fd) == -1)
    	{
    	    perror("Pipe");
    	    global.exit_code = 1;
    	    return (-1);
    	}
    	ret = execute_both_pipe_nodes(node->content->pipe, pipe_fd, &pid2, data);
    	close(pipe_fd[0]);
    	close(pipe_fd[1]);
	waitpid(pid2, NULL, 0);
    	return (ret);
}

int	execute_both_pipe_nodes(t_pipe *pipe, int pipe_fd[2], int *pid2, t_data *data)
{
    	int	ret;

    	ret = execute_left_node(pipe->left, pipe_fd, data);
    	*pid2 = fork();
    	if (*pid2 == -1)
    	{
    	    perror("Fork");
    	    global.exit_code = 1;
    	    return (-1);
    	}
    	else if (*pid2 == 0)
    	{
    	    ret = execute_right_node(pipe->right, pipe_fd, data);
    	    exit(0);
    	}
    	return (ret);
}

int	execute_ast(t_data *data)
{
	if (data->commands_tree->root)
	{
		ft_make_here_doc(data->commands_tree->root, data);
		if (data->commands_tree->root->type == AST_CMD)
			return (execute_cmd_node(data->commands_tree->root, data));
		else
			return (execute_pipe_node(data->commands_tree->root, data));
	}
	return (0);
}
