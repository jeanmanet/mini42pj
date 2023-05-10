/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:09:11 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/10 12:16:29 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_echo(t_com *command)
{
	int	i;

	i = 0;
	if (!command->args[1])
	{
		printf("\n");
		return (0);
	}
	if (!ft_strncmp(command->args[1], "-n", 3))
		i = 2;
	else
		i = 1;
	while (command->args[i])
	{
		ft_putstr_fd(command->args[i], 1);
		i++;
		if (command->args[i])
			write(1, " ", 1);
	}
	if (ft_strncmp(command->args[1], "-n", 3))
		write(1, "\n", 1);
	return (0);
}
