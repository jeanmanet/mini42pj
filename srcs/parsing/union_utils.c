/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 08:37:06 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/30 20:37:38 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_union	*init_cmd_union(t_com *command)
{
	t_union	*cmd_union;

	cmd_union = malloc(sizeof(t_union));
	if (!cmd_union)
		ft_exit_error("Memmory allocation error \n");
	cmd_union->cmd = command;
	return (cmd_union);
}

t_union	*init_pipe_union(void)
{
	t_union	*pipe_union;
	t_pipe	*pipe_node;

	pipe_union = malloc(sizeof(t_union));
	pipe_node = malloc(sizeof(t_pipe));
	if (!pipe_union || !pipe_node)
		ft_exit_error("Memmory allocation error \n");
	pipe_union->pipe = pipe_node;
	pipe_union->pipe->left = NULL;
	pipe_union->pipe->right = NULL;
	return (pipe_union);
}
