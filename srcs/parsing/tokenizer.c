/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:55:24 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/11 14:39:34 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_inquote_token(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = str[i];
	while (str[i + 1] != c)
		i++;
	return (i + 2);
}

int	get_next_token(char *str)
{
	int	i;

	i = 0;
	if (str[i] && ft_lexing(str[i]) == LEX_PIPE)
		return (1);
	if (str[i] && (ft_lexing(str[i]) == LEX_GREATER
			|| ft_lexing(str[i]) == LEX_SMALLER))
	{
		if (ft_lexing(str[i + 1]) == ft_lexing(str[i]))
			return (2);
		else
			return (1);
	}
	if (str[i] && (ft_lexing(str[i]) == LEX_SQUOTE
			|| ft_lexing(str[i]) == LEX_DQUOTE))
		return (get_inquote_token(str));
	if (str[i] && ft_lexing(str[i]) == LEX_WORD)
		while (str[i] && ft_lexing(str[i]) == LEX_WORD)
			i++;
	return (i);
}

void	get_token_type(t_token_node *token_list)
{
	while (token_list)
	{
		if ((ft_lexing(token_list->token[0]) == LEX_WORD)
			|| token_list->q_state <= S_IN_DQUOTE)
			token_list->type = T_ARG;
		if ((ft_lexing(token_list->token[0]) == LEX_GREATER)
			&& token_list->q_state == S_NOT_IN_QUOTE)
		{
			token_list->type = T_REDIR_OUT;
			token_list = token_list->next;
			token_list->type = T_REDIR_OUT;
		}
		if ((ft_lexing(token_list->token[0]) == LEX_SMALLER)
			&& token_list->q_state == S_NOT_IN_QUOTE)
		{
			token_list->type = T_REDIR_IN;
			token_list = token_list->next;
			token_list->type = T_REDIR_IN;
		}
		if ((ft_lexing(token_list->token[0]) == LEX_PIPE)
			&& token_list->q_state == S_NOT_IN_QUOTE)
			token_list->type = T_PIPE;
		token_list = token_list->next;
	}
}

t_token_node	*tokenizer(char *commandline)
{
	t_token_node	*token_list;
	t_flag_var_join	flags;

	token_list = NULL;
	flags.flag_len_zero = 1;
	flags.flag_export_detected = 0;
	tokenize_commandline(0, commandline, &token_list, &flags);
	get_token_type(token_list);
	return (token_list);
}

void	tokenize_commandline(int start, char *commandline,
t_token_node **token_list, t_flag_var_join *flags)
{
	size_t		len;
	char		*temp;

	while (commandline[start])
	{
		len = get_next_token(&commandline[start]);
		if (len == 0)
			flags->flag_len_zero = 0;
		if (ft_lexing(commandline[start]) <= LEX_DQUOTE)
		{
			if (ft_lexing(commandline[start]) <= LEX_PIPE)
				temp = ft_substr(commandline, start, len);
			else
				temp = ft_substr(commandline, start + 1, len - 2);
			add_token_node(token_list, temp,
				ft_lexing(commandline[start]), flags);
			start += (int)len;
			free(temp);
		}
		else
			start++;
	}
}
