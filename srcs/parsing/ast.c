/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:52:27 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/23 15:17:48 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_ast_node(t_data *data, t_union *content, int type)
{
	t_ast_node	*new_node;

	new_node = malloc(sizeof(t_ast_node));
	if (!new_node)
		ft_exit_error("Memory allocation error !\n");
	if (type == AST_PIPE)
	{
		new_node->type = AST_PIPE;
		new_node->content = content;
		new_node->content->pipe->left = data->commands_tree->root;
		data->commands_tree->root = new_node;
	}
	if (type == AST_CMD)
	{
		new_node->type = type;
		new_node->content = content;
		if (data->commands_tree->root == NULL)
			data->commands_tree->root = new_node;
		else
			data->commands_tree->root->content->pipe->right = new_node;
	}
}
