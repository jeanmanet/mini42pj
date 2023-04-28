/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:26:37 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/28 15:39:23 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_com	*current_command_init(t_token_node *token_list)
{
	t_com	*cmd;
	char	**args;
	int		i;

	i = 0;
	while (token_list && token_list->type != T_PIPE)
	{
		if (token_list->type == T_ARG)
			i++;
		token_list = token_list->next;
	}
	cmd = malloc(sizeof(t_com));
	args = malloc(sizeof(char *) * (i + 1));
	if (!cmd || !args)
		ft_exit_error("Memory Allocation Error \n");
	cmd->args = args;
	cmd->cmd_input_mode = CMD_STDIN;
	cmd->cmd_output_mode = CMD_STDOUT;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->here_doc_limiter = NULL;
	return (cmd);
}

t_token_node	*go_to_next_token_type(t_token_node *token_list_head)
{
	while (token_list_head && token_list_head->type != T_PIPE)
		token_list_head = token_list_head->next;
	return (token_list_head);
}

int	get_openfile_type(char *token)
{
	int	openfile_type;

	openfile_type = 0;
	if (token[0] == '<')
	{
		if (token[1] == '<')
			openfile_type = (CMD_HERE_DOC);
		else
			openfile_type = (CMD_INFILE);
	}
	else if (token[0] == '>')
	{
		if (token[1] == '>')
			openfile_type = (CMD_APPEND);
		else
			openfile_type = (CMD_TRUNC);
	}
	return (openfile_type);
}

t_com	*get_command_node(t_token_node *token_list)
{
	t_com	*command;
	int	i;

	i = 0;
	command = current_command_init(token_list);
	while (token_list && token_list->type != T_PIPE)
	{
		if (token_list->type == T_ARG)
			command->args[i++] = token_list->token;
		else if (token_list->type == T_REDIR_IN)
		{
			command->cmd_input_mode = get_openfile_type(token_list->token);
			token_list = token_list->next;
			command->infile = token_list->token;
		}
		else if (token_list->type == T_REDIR_OUT)
		{
			command->cmd_output_mode = get_openfile_type(token_list->token);
			token_list = token_list->next;
			command->outfile = token_list->token;
		}
		token_list = token_list->next;
	}
	command->args[i] = NULL;
	return (command);
}

void	parse_token_list(t_data *data)
{
	t_com		*current_command;
	t_token_node	*token_list_head;

	token_list_head = data->token_list;
	while (token_list_head)
	{
		if (token_list_head->type != T_PIPE)
		{
			current_command = get_command_node(token_list_head);
			token_list_head = go_to_next_token_type(token_list_head);
		}
		else
		{
			token_list_head = token_list_head->next;
			add_ast_node(data, init_cmd_union(current_command), AST_CMD);
			add_ast_node(data, init_pipe_union(), AST_PIPE);
		}
	}
	add_ast_node(data, init_cmd_union(current_command), AST_CMD);
}
