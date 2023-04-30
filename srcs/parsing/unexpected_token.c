/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpected_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:34:02 by ory               #+#    #+#             */
/*   Updated: 2023/04/30 20:34:36 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unexpected_token(char *command_line)
{
	int	i;

	i = 0;
	while(command_line[i])
		i++;
	i = i - 1;
	if (command_line[i] == '<' || command_line[i] == '>' || command_line[i] == '|' || command_line[0] == '|')
	{
		printf("syntax error: unexpected token\n");
		global.exit_code = 258;
		return (1);
	}
	return (0);
}

int unexpected_token_2(t_data *data)
{
    t_token_node	*tmp_list;
    int			return_val;

    tmp_list = data->token_list;
    return_val = check_for_unexpected_tokens(tmp_list);
    return (return_val);
}

int	check_for_unexpected_tokens(t_token_node *token_list)
{
	while (token_list && token_list->next)
    	{
    	    if ((token_list->type == 1 || token_list->type == 2 || token_list->type == 4) && 
    	        (token_list->next->type == 1 || token_list->next->type == 2 || token_list->next->type == 4))
    	    {
    	        if (!(token_list->type == 4 && token_list->next->type == 1))
    	        {
    	            if (((token_list->type == 1 || token_list->type == 2 || token_list->type == 4)) &&
    	                is_only_compose_by_redir_char(token_list->token) && is_only_compose_by_redir_char(token_list->next->token))
    	            {
    	                if (token_list->type == 1 && token_list->next->type == 2)
    	                {
    	                    token_list = token_list->next;
    	                    continue;
    	                }
    	                printf("syntax error: unexpected token `%s'\n", token_list->next->token);
			global.exit_code = 258;
    	                return (1);
    	            }
    	        }
    	    }
    	    token_list = token_list->next;
    	}
    	return (0);
}
