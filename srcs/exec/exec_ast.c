/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:05:35 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/30 19:20:26 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	execute_pipe_node(t_ast_node *node, t_data *data);

// int	execute_cmd_node(t_ast_node *node, t_data *data)
// {
// 	int	returnval;

// 	returnval = exec_command(node->content->cmd, data);
// 	return (returnval);
// }

// int	execute_left_node(t_ast_node *left, int *pipe_fd, t_data *data)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("Fork");
// 		return (-1);
// 	}
// 	else if (pid == 0)
// 	{
// 		close(pipe_fd[0]);
// 		dup2(pipe_fd[1], STDOUT_FILENO);
// 		if (left->type == AST_CMD)
// 			execute_cmd_node(left, data);
// 		else
// 			execute_pipe_node(left, data);
// 		exit(0);
// 	}
// 	waitpid(pid, NULL, 0);
// 	return (0);
// }

// int	execute_right_node(t_ast_node *right, int *pipe_fd, t_data *data)
// {
// 	int	returnval;

// 	close(pipe_fd[1]);
// 	dup2(pipe_fd[0], STDIN_FILENO);
// 	returnval = execute_cmd_node(right, data);
// 	return (returnval);
// }

// int	execute_pipe_node(t_ast_node *node, t_data *data)
// {
// 	int		pipe_fd[2];
// 	int		ret;
// 	pid_t	pid2;

// 	if (pipe(pipe_fd) == -1)
// 	{
// 		perror("Pipe");
// 		return (-1);
// 	}
// 	ret = execute_left_node(node->content->pipe->left, pipe_fd, data);
// 	pid2 = fork();
// 	if (pid2 == -1)
// 	{
// 		perror("Fork");
// 		return (-1);
// 	}
// 	else if (pid2 == 0)
// 	{
// 		ret = execute_right_node(node->content->pipe->right, pipe_fd, data);
// 		exit(0);
// 	}
// 	close(pipe_fd[0]);
// 	close(pipe_fd[1]);
// 	waitpid(pid2, NULL, 0);
// 	return (ret);
// }

// int	execute_ast(t_data *data)
// {
// 	if (data->commands_tree->root)
// 	{
// 		if (data->commands_tree->root->type == AST_CMD)
// 			return (execute_cmd_node(data->commands_tree->root, data));
// 		else
// 			return (execute_pipe_node(data->commands_tree->root, data));
// 	}
// 	return (0);
// }

int	execute_pipe_node(t_ast_node *node, t_data *data);

int	execute_cmd_node(t_ast_node *node, t_data *data)
{
	int	returnval;

	returnval = exec_command(node->content->cmd, data);
	return (returnval);
}

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

// int	execute_pipe_node(t_ast_node *node, t_data *data)
// {
// 	int		pipe_fd[2];
// 	int		ret;
// 	pid_t	pid2;

// 	if (pipe(pipe_fd) == -1)
// 	{
// 		perror("Pipe");
// 		global.exit_code = 1;
// 		return (-1);
// 	}
// 	ret = execute_left_node(node->content->pipe->left, pipe_fd, data);
// 	pid2 = fork();
// 	if (pid2 == -1)
// 	{
// 		perror("Fork");
// 		global.exit_code = 1;
// 		return (-1);
// 	}
// 	else if (pid2 == 0)
// 	{
// 		ret = execute_right_node(node->content->pipe->right, pipe_fd, data);
// 		exit(0);
// 	}
// 	close(pipe_fd[0]);
// 	close(pipe_fd[1]);
// 	waitpid(pid2, NULL, 0);
// 	return (ret);
// }

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
