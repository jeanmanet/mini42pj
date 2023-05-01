/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:31:12 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/01 22:21:48 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(void)
{
	if(global.g_pid == 0)
	{
		global.exit_code = 1;
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		kill(global.g_pid, SIGINT);
		global.g_pid = 0;
		global.exit_code = 130;
		printf("\n");
		rl_on_new_line();
	}
}

void	handle_sigquit(void)
{
	if (global.g_pid == 0)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		kill(global.g_pid, SIGINT);
		global.g_pid = 0;
		global.exit_code = 131;
		printf("Quit: 3\n");
		rl_on_new_line();
	}
}

void	ft_sigaction(int signal)
{
	if (signal == SIGINT)
		handle_sigint();
	if (signal == SIGQUIT)
		handle_sigquit();
}

void	ft_signal_handler(void)
{
	struct sigaction	sigact;

	sigact.sa_handler = ft_sigaction;
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGQUIT, &sigact, NULL);
}

void	ft_signal_handler_here_doc(int signal)
{
	if (signal == SIGINT)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
	}
}

 
