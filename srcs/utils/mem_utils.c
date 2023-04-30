/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:51:45 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/30 19:40:42 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token_node **list_head)
{
	t_token_node	*current_node;
	t_token_node	*temp_node;

	current_node = *list_head;
	while (current_node != NULL)
	{
		temp_node = current_node;
		current_node = current_node->next;
		free(temp_node->token);
		free(temp_node);
	}
	*list_head = NULL;
}

void	free_cmd_node(t_ast_node	*cmd_node)
{
	free(cmd_node->content->cmd->args);
	free(cmd_node->content->cmd);
	free(cmd_node->content);
	free(cmd_node);
}

void	free_pipe_node(t_ast_node	*pipe_node)
{
	if (pipe_node->content->pipe->left->type == AST_PIPE)
		free_pipe_node(pipe_node->content->pipe->left);
	else
		free_cmd_node(pipe_node->content->pipe->left);
	free_cmd_node(pipe_node->content->pipe->right);
	free(pipe_node->content->pipe);
	free(pipe_node->content);
	free(pipe_node);
}

void free_ast(t_ast *ast_tree)
{
    if (ast_tree == NULL)
        return;
    if (ast_tree->root != NULL)
    {
        if (ast_tree->root->type == AST_CMD)
            free_cmd_node(ast_tree->root);
	else
            free_pipe_node(ast_tree->root);
        ast_tree->root = NULL;
    }
}

void	free_mem(t_data *data)
{
	free(data->command_line);
	free_tokens(&data->token_list);
	free_ast(data->commands_tree);
}
