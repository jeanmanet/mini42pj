/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_assignment_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:58:50 by ory               #+#    #+#             */
/*   Updated: 2023/05/09 19:03:18 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unexpected_var_assignment(t_data *data)
{
	t_token_node	*list_token;

	list_token = data->token_list;
	while (list_token)
	{
		if (list_token->type == T_ARG)
		{
			if (list_token->token && ft_ischarset(list_token->token, '='))
			{
				if (list_token->token[ft_strlen(list_token->token) - 1] == '=')
					return (1);
				if ((list_token->next == NULL || list_token->next->type < 4))
				{
					if (unexpected_char_in_name(list_token->token))
					{
						printf("%s: command not found\n", list_token->token);
						g_global.code_error = 127;
						return (1);
					}
				}
			}
		}
		list_token = list_token->next;
	}
	return (0);
}

void	invalid_assignment(t_data *data)
{
	t_token_node	*list_token;

	list_token = data->token_list;
	while (list_token)
	{
		if (list_token->type == T_ARG)
		{
			if (list_token->token && ft_ischarset(list_token->token, '='))
				list_token->var_assignment = 0;
		}
		list_token = list_token->next;
	}
}

int	unexpected_char_in_name(char *str)
{
	int		i;
	char	*name;

	i = -1;
	name = NULL;
	if ((str[0] != '$' && !ft_isalpha(str[0])) || !ft_isalpha(str[0]))
		return (1);
	name = extract_name_in_assignment(str);
	i = -1;
	while (name[++i])
	{
		if ((!ft_isalnum(str[i]) && !ft_isalpha(str[i])) && (str[i] != '_'))
		{
			free(name);
			return (1);
		}
	}
	if (name)
		free(name);
	return (0);
}
