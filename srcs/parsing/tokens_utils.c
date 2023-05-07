/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:36:51 by ory               #+#    #+#             */
/*   Updated: 2023/05/07 13:26:16 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_flag_for_join_with_prev_token(t_token_node **list_head,
	int *flag_len_zero)
{
	int				flag_for_join_with_prev_token;
	t_token_node	*current_node;

	flag_for_join_with_prev_token = 0;
	if (*list_head)
	{
		current_node = *list_head;
		while (current_node->next != NULL)
			current_node = current_node->next;
		if (current_node->token[ft_strlen(current_node->token) - 1]
			== '=' && *flag_len_zero == 1)
			flag_for_join_with_prev_token = 1;
	}
	return (flag_for_join_with_prev_token);
}

void	print_tokens(t_token_node *list_head)
{
	t_token_node	*current_node;

	current_node = list_head;
	while (current_node != NULL)
	{
		printf("Tokens dans la liste : \n");
		printf("[%s] type = %d var_assignment = %d    ", current_node->token,
			current_node->type, current_node->var_assignment);
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
