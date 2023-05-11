/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:09:11 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/12 01:43:36 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_param_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	ft_echo(t_com *command)
{
	int	i;

	i = 1;
	if (!command->args[1])
	{
		printf("\n");
		return (0);
	}
	while (command->args[i])
	{
		if (!is_param_n(command->args[i]))
			break ;
		i++;
	}
	while (command->args[i])
	{
		ft_putstr_fd(command->args[i], 1);
		i++;
		if (command->args[i])
			write(1, " ", 1);
	}
	if (!is_param_n(command->args[1]))
		write(1, "\n", 1);
	return (0);
}
