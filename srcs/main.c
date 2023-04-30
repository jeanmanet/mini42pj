/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:03:37 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/30 21:06:06 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global global;

int	check_quotes(char *str)
{
	int	i;
	int	nb_quotes;
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
		print_error("Error in command, some quotes aren't closed \n", 2);
	return (!(nb_quotes % 2));
}

void	prompt(t_data *data)
{
	ft_signal_handler();
	data->command_line = readline("minishell > ");
	add_history(data->command_line);
	if (data->command_line)
	{
		ft_command_line(data);
		if (global.g_pid != 0)
		{
			kill(global.g_pid, SIGINT);
			global.g_pid = 0;
		}
	}
	else
	{
		printf("exit\n");
		system("leaks minishell");
		exit(0);
	}
}

void	ft_command_line(t_data *data)
{
	if (ft_strlen(data->command_line) > 0
			&& check_quotes(data->command_line) && !unexpected_token(data->command_line))
	{
		data->token_list = tokenizer(data->command_line);
		if (!unexpected_token_2(data))
		{
			if (replace_var_by_value(data))
				ft_add_var(data);
			parse_token_list(data);
			execute_ast(data);
		}
		free_mem(data);
	}
	else
		free(data->command_line);
}

t_data	*data_init(char **envp)
{
	t_data	*data;

	global.g_pid = 0;
	global.exit_code = 0;
	data = malloc(sizeof(*data));
	if (!data)
		ft_exit_error("Memory allocation error \n");
	data->commands_tree = malloc(sizeof(t_ast));
	if (!data->commands_tree)
		ft_exit_error("Memory allocation error \n");
	data->commands_tree->root = NULL;
	data->envp = ft_import_envp(envp);
	data->pid = 0;
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	data = data_init(envp);
	if (argc > 1)
	{
		printf("Invalid argument(s), ");
		printf("this minishell doesn't execute scriptfiles !\n");
	}
	else
		while (1)
			prompt(data);
	return (0);
}
