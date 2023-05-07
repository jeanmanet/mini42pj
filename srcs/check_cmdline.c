/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:49:22 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/07 13:58:37 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quotes(char *str)
{
	int		i;
	int		nb_quotes;
	char	c;

	i = 0;
	nb_quotes = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if ((ft_lexing(str[i]) == LEX_SQUOTE)
			|| (ft_lexing(str[i]) == LEX_DQUOTE))
		{
			c = str[i++];
			nb_quotes++;
			while (str[i] && str[i] != c)
				i++;
			if (str[i] == c)
				nb_quotes++;
		}
		i++;
	}
	if (nb_quotes % 2 != 0)
		printf("Error in command, some quotes aren't closed \n");
	return (!(nb_quotes % 2));
}

int	cmdline_is_only_spaces(char *cmdline)
{
	int	i;

	i = 0;
	while (cmdline[i])
	{
		if (!ft_isspace(cmdline[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_cmdline(char *cmdline)
{
	int	ret;

	ret = 0;
	if (!(ft_strlen(cmdline) > 0))
		ret = -1;
	if (!check_quotes(cmdline))
		ret = -1;
	if (cmdline_is_only_spaces(cmdline))
		ret = -1;
	if (unexpected_token(cmdline))
		ret = -1;
	return (ret);
}
