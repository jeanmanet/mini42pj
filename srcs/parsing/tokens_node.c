/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:36:14 by ory               #+#    #+#             */
/*   Updated: 2023/05/07 13:24:09 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_node	*init_token_node(char *token, int flag_for_join_with_prev_token)
{
	t_token_node	*new_node;

	new_node = malloc(sizeof(t_token_node));
	if (new_node == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(1);
	}
	new_node->token = malloc(strlen(token) + 1);
	if (new_node->token == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(1);
	}
	ft_strlcpy(new_node->token, token, ft_strlen(token)+ 1);
	new_node->var_assignment = 1;
	new_node->flag_for_join_with_prev_token = flag_for_join_with_prev_token;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

t_token_node	*create_token_node(char *token, int state,
	int flag_for_join_with_prev_token)
{
	t_token_node	*new_node;

	new_node = init_token_node(token, flag_for_join_with_prev_token);
	if (state == LEX_DQUOTE)
		new_node->q_state = S_IN_DQUOTE;
	else if (state == LEX_SQUOTE)
		new_node->q_state = S_IN_SQUOTE;
	else
		new_node->q_state = S_NOT_IN_QUOTE;
	return (new_node);
}

void	add_token_node(t_token_node **list_head,
	char *token, int state, int *flag_len_zero)
{
	t_token_node	*new_node;
	t_token_node	*current_node;
	int				flag_for_join_with_prev_token;

	flag_for_join_with_prev_token = \
		get_flag_for_join_with_prev_token(list_head, flag_len_zero);
	new_node = create_token_node(token, state, flag_for_join_with_prev_token);
	if (*flag_len_zero == 0)
		*flag_len_zero = 1;
	if (*list_head == NULL)
	{
		*list_head = new_node;
		return ;
	}
	current_node = *list_head;
	while (current_node->next != NULL)
		current_node = current_node->next;
	current_node->next = new_node;
	new_node->prev = current_node;
}

void	delete_token_node(t_token_node **node)
{
	t_token_node		*prev_node;
	t_token_node		*next_node;

	if (*node == NULL)
		return ;
	prev_node = (*node)->prev;
	next_node = (*node)->next;
	if (prev_node != NULL)
		prev_node->next = next_node;
	if (next_node != NULL)
		next_node->prev = prev_node;
	free((*node)->token);
	free(*node);
	*node = NULL;
}
