/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:06:28 by ory               #+#    #+#             */
/*   Updated: 2023/05/11 16:07:45 by ory              ###   ########.fr       */
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
		if (list_tokens->prev
			&& list_tokens->flag_for_join_with_prev_token == 1)
		{
			new_str = ft_strjoin(list_tokens->prev->token, list_tokens->token);
			free(list_tokens->prev->token);
			list_tokens->prev->token = ft_strdup(new_str);
			list_tokens->prev->flag_for_join_with_prev_token = 2;
			free(new_str);
			delete_token_node(&list_tokens);
			list_tokens = data->token_list;
		}
		else
			list_tokens = list_tokens->next;
	}
}

int	cmd_not_found_in_list(t_data *data)
{
	t_token_node	*list_tokens;

	list_tokens = data->token_list;
	while (list_tokens)
	{
		if (list_tokens->type == T_ARG && (list_tokens->q_state == 2
				&& !ft_ischarset(list_tokens->token, '=')))
		{
			if (!arg_is_a_cmd(data, list_tokens->token))
			{
				cmd_not_found(list_tokens->token);
				return (1);
			}
		}
		list_tokens = list_tokens->next;
	}
	return (0);
}

void	var_assignment(t_data *data)
{
	t_token_node	*list_tokens;

	list_tokens = data->token_list;
	while (list_tokens)
	{
		if (list_tokens->type == T_PIPE)
			return ;
		list_tokens = list_tokens->next;
	}
	list_tokens = data->token_list;
	while (list_tokens)
	{
		if (arg_is_a_cmd(data, list_tokens->token))
			if (list_tokens->prev && list_tokens->prev->type != 1
				&& list_tokens->prev->type != 2)
				return ;
		if (list_tokens->type == T_ARG && list_tokens->token
			&& ft_ischarset(list_tokens->token, '=')
			&& list_tokens->q_state == 2)
			list_tokens->type = T_VAR;
		list_tokens = list_tokens->next;
	}
	list_tokens = data->token_list;
	add_var(data);
}

void	add_var(t_data *data)
{
	t_token_node	*list_tokens;

	list_tokens = data->token_list;
	while (list_tokens)
	{
		if (list_tokens->next == NULL || list_tokens->next->type < 4)
		{
			if (list_tokens->var_assignment == 1 && list_tokens->type == T_VAR)
				add_var_in_list(data, list_tokens->token);
		}
		list_tokens = list_tokens->next;
	}
}
