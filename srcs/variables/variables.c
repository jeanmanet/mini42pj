/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:58:40 by ory               #+#    #+#             */
/*   Updated: 2023/04/30 21:00:44 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*var_exist_outside_env(t_data *data, char *var_name)
{
	t_lst_var	*tmp;

	tmp = data->var_list;
	if (!var_name)
		return (NULL);
	while(tmp)
	{
		if (ft_strcmp(var_name, tmp->name) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_var_in_list(t_data *data, char *str)
{
	char	*name;
	char	*value;
	int	index;
	int	i;
	int	flag_plus;
	
	name = NULL;
	value = NULL;
	index = get_name_and_index(str, &name, &flag_plus, &i);
	value = ft_substr(str, index, i - index);
	if (check_if_var_is_for_env(name, value, data, flag_plus) == 0)
		lst_add_var(data, name, value, flag_plus);
	free(name);
	free(value);
}

int	get_name_and_index(char *str, char **name, int *flag_plus, int *i)
{
	int	index;
	
	*i = 0;
	*flag_plus = 0;
	index = 0;
	while(str[*i])
	{
	    if (str[*i] == '=' || str[*i] == '+')
	    {
			if (str[*i] == '+' && str[*i + 1] == '=')
				*flag_plus = 2;
	        *name = ft_substr(str, 0, *i);
	        index = *i + 1;
	        break;
	    }
	    (*i)++;
	}
	return index;
}

void	ft_add_var(t_data *data)
{
	t_token_node	*list_tokens;
	char		*cmd;

	list_tokens = data->token_list;
	join_var_was_splited_in_tokenizer(data);
	while(list_tokens)
	{
		if (cmd_is_builtin_2(list_tokens->token))
			return ;
		if ((cmd = str_is_cmd(list_tokens->token, data->envp)))
		{
			free(cmd);
			return ;
		}
		list_tokens = list_tokens->next;
	}
	if (unexpected_var_assignment(data))
	 	invalid_assignment(data);
	var_assignment(data);
}

void var_assignment(t_data *data)
{
	t_token_node	*list_tokens;
	
	list_tokens = data->token_list;
	while (list_tokens)
	{
		if (list_tokens->type == T_ARG && list_tokens->token && ft_ischarset(list_tokens->token, '='))
		{
			list_tokens->type = T_VAR;
			if (list_tokens->next == NULL || list_tokens->next->type < 4)
			{
				if (list_tokens->var_assignment == 1)
					add_var_in_list(data, list_tokens->token);
			}
		}
		list_tokens = list_tokens->next;
	}
}