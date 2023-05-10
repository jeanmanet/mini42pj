/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:23:16 by ory               #+#    #+#             */
/*   Updated: 2023/05/10 09:18:41 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	check_exit_args(t_com *command, t_data *data)
{
	int	i;

	i = 1;
	while (command->args[i])
		i++;
	i--;
	if (i > 1 && str_is_only_digit(command->args[1]))
	{
		printf("exit\nminishell: exit: too many arguments\n");
		g_global.code_error = 1;
	}
	else if (!str_is_only_digit(command->args[1]))
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n",
			command->args[1]);
		free_mem(data);
		exit(255);
	}
	else
	{
		printf("exit\n");
		exit(ft_atoi(command->args[1]));
	}
}

int	ft_exit(t_com *command, t_data *data)
{
	if (command->args[1])
		check_exit_args(command, data);
	else
	{
		free_mem(data);
		exit(0);
	}
	return (0);
}

int	str_is_only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
