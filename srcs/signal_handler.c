/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:31:12 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/30 21:38:44 by ory              ###   ########.fr       */
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

// void	ft_signal_handler_here_doc(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		global.tmp_fd_here_doc = -2;
// 		// if (global.fd_here_doc != -1)
// 		//close(global.fd_here_doc);
// 		//printf("handler ctrl c heredoc\n");

// 		// printf("\e[2K");
// 		// rl_on_new_line();
// 		// rl_redisplay();

// 		// rl_on_new_line();
// 		// write(0, "\x04", 1);
// 		//unlink(".here_doc.tmp");
// 	}
// 	else if (signal == SIGQUIT)
// 	{
// 		printf("\e[2K");
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

void	ft_signal_handler_here_doc(int signal)
{
	if (signal == SIGINT)
	{
		if (global.fd_here_doc != -2) // vérifie que le here_doc est ouvert
		{
			//close(global.fd_here_doc); // ferme le fichier du here_doc
			global.fd_here_doc = -2; // réinitialise le descripteur de fichier du here_doc
			printf("\n"); // affiche une nouvelle ligne
			//prompt(); // affiche le prompt de minishell
		}
	}
	else if (signal == SIGQUIT)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
	}
}
