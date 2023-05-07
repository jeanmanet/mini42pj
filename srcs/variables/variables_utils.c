/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:06:28 by ory               #+#    #+#             */
/*   Updated: 2023/05/07 13:53:05 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	join_var_was_splited_in_tokenizer(t_data *data)
{
	t_token_node	*list_tokens;
	char			*new_str;

	list_tokens = data->token_list;
	while (list_tokens)
	{
		if (list_tokens->flag_for_join_with_prev_token == 1)
		{
			new_str = ft_strjoin(list_tokens->prev->token, list_tokens->token);
			free(list_tokens->prev->token);
			list_tokens->prev->token = ft_strdup(new_str);
			free(new_str);
			delete_token_node(&list_tokens);
			list_tokens = data->token_list;
		}
		else
			list_tokens = list_tokens->next;
	}
}
