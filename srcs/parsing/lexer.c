/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:06:37 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/07 13:24:21 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_lexing(char c)
{
	if (ft_isspace(c))
		return (LEX_SPACE);
	else if (c == '<')
		return (LEX_SMALLER);
	else if (c == '>')
		return (LEX_GREATER);
	else if (c == '|')
		return (LEX_PIPE);
	else if (c == '\'')
		return (LEX_SQUOTE);
	else if (c == '"')
		return (LEX_DQUOTE);
	return (LEX_WORD);
}

int	is_only_compose_by_redir_char(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (len == 1)
		if (str[i] == '|')
			return (1);
	if (str_is_only_this_char(str, '<'))
		return (1);
	if (str_is_only_this_char(str, '>'))
		return (1);
	return (0);
}

int	str_is_only_this_char(char *str, int c)
{
	int	i;
	int	len;
	int	match;

	i = 0;
	match = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == c)
			match++;
		i++;
	}
	if (match == len)
		return (1);
	return (0);
}
