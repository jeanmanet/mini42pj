/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:07:26 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/28 15:38:51 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_node	*create_token_node(char *token, int state, int flag_for_join_with_prev_token)
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
	if (state == LEX_DQUOTE)
		new_node->q_state = S_IN_DQUOTE;
	else if (state == LEX_SQUOTE)
		new_node->q_state = S_IN_SQUOTE;
	else
		new_node->q_state = S_NOT_IN_QUOTE;
	new_node->var_assignment = 1;
	new_node->flag_for_join_with_prev_token = flag_for_join_with_prev_token;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	add_token_node(t_token_node **list_head, char *token, int state, int *flag_len_zero)
{
	t_token_node	*new_node;
	t_token_node	*current_node;
	int		flag_for_join_with_prev_token;

	flag_for_join_with_prev_token = 0;
	if (*list_head)
	{
		current_node = *list_head;
		while (current_node->next != NULL)
			current_node = current_node->next;
		if (current_node->token[ft_strlen(current_node->token) - 1] == '=' && *flag_len_zero == 1)
			flag_for_join_with_prev_token = 1;
	}
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

void	print_tokens(t_token_node *list_head)
{
	t_token_node	*current_node;

	current_node = list_head;
	while (current_node != NULL)
	{
		printf("Tokens dans la liste : \n");
		printf("[%s] ", current_node->token);
		if (current_node->q_state == S_IN_SQUOTE)
			printf("-> IN_SQUOTE ,");
		else if (current_node->q_state == S_IN_DQUOTE)
			printf("-> IN_DQUOTE ,");
		else if (current_node->q_state == S_NOT_IN_QUOTE)
			printf("-> NOT_IN_QUOTE ,");
		if (current_node->type == T_ARG)
			printf(" type : ARG \n");
		else if (current_node->type == T_REDIR_IN)
			printf(" type : REDIR IN \n");
		else if (current_node->type == T_REDIR_OUT)
			printf(" type : REDIR OUT \n");
		else if (current_node->type == T_PIPE)
			printf(" type : PIPE \n");
		current_node = current_node->next;
	}
	printf("fin de la liste\n\n");
}

void delete_token_node(t_token_node **node)
{
	t_token_node	*prev_node;
    	t_token_node	*next_node;

    	if (*node == NULL)
    	    return;
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

