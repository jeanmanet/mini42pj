/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpected_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:34:02 by ory               #+#    #+#             */
/*   Updated: 2023/05/08 10:20:13 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unexpected_token(char *command_line)
{
	int	i;

	i = 0;
	while (command_line[i])
		i++;
	i = i - 1;
	if (command_line[i] == '<' || command_line[i] == '>'
		|| command_line[i] == '|' || command_line[0] == '|')
	{
		printf("syntax error: unexpected token\n");
		g_global.exit_code = 258;
		return (1);
	}
	return (0);
}

int	unexpected_token_2(t_data *data)
{
	t_token_node	*tmp_list;
	int				return_val;

	tmp_list = data->token_list;
	return_val = check_for_unexpected_tokens(tmp_list);
	return (return_val);
}

int	tokens_are_redir(t_token_node *token1, t_token_node *token2)
{
	if ((token1->type == 1 || token1->type == 2
			|| token1->type == 4) && (token2->type == 1 || token2->type == 2
			|| token2->type == 4))
		return (1);
	else
		return (0);
}

void	print_error_unexpected_token(char *str)
{
	printf("syntax error: unexpected token `%s'\n", str);
}

int	check_for_unexpected_tokens(t_token_node *token_list)
{
	while (token_list && token_list->next)
	{
		if (tokens_are_redir(token_list, token_list->next))
		{
			if (!(token_list->type == 4 && token_list->next->type == 1))
			{
				if (tokens_are_redir(token_list, token_list->next)
					&& is_only_compose_by_redir_char(token_list->token)
					&& is_only_compose_by_redir_char(token_list->next->token))
				{
					if (token_list->type == 1 && token_list->next->type == 2)
					{
						token_list = token_list->next;
						continue ;
					}
					print_error_unexpected_token(token_list->next->token);
					g_global.exit_code = 258;
					return (1);
				}
			}
		}
		token_list = token_list->next;
	}
	return (0);
}
