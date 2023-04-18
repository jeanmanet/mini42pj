/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:03:37 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/18 21:04:21 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global global;

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

void	ft_add_var(t_data *data)
{
	t_token_node	*list_tokens;
	char		*cmd;

	list_tokens = data->token_list;
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
	list_tokens = data->token_list;
	while (list_tokens)
	{
		if (list_tokens->q_state == S_NOT_IN_QUOTE && list_tokens->type == T_ARG)
		{
			// if (list_tokens->prev)
			// {
			// 	// if (ft_strcmp(list_tokens->prev->token, "export") == 0)
			// 	// 	return ;
			// 	// if (ft_strcmp(list_tokens->prev->token, "unset") == 0)
			// 	// 	return ;
			// 	if (cmd_is_builtin(data->command_line))
			// 		return ;
			// 	if (get_absolute_command())
				
			// }
			if (list_tokens->token && ft_ischarset(list_tokens->token, '='))
			{
				list_tokens->type = T_VAR;
				if (list_tokens->next == NULL || list_tokens->next->type < 4)
				{
					if (unexpected_char_in_name(list_tokens->token))
					{
						printf("%s: command not found\n", list_tokens->token);
						return ;
					}
					add_var_in_list(data, list_tokens->token);
				}
			}
		}
		list_tokens = list_tokens->next;
	}
}

int	unexpected_char_in_name(char *str)
{
	int	i;
	char	*name;

	i = -1;
	name = NULL;
	if ((str[0] != '$' && !ft_isalpha(str[0]) ) || !ft_isalpha(str[0]))
		return (1);
	name = extract_name_in_assignment(str);
	i = -1;
	while(name[++i])
	{
		if ((!ft_isalnum(str[i]) && !ft_isalpha(str[i])) && (str[i] != '_'))
		{
			free(name);
			return (1);
		}
	}
	if (name)
		free(name);
	return (0);
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
			printf("token = %s type = %d\n", data->token_list->token, data->token_list->type);
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
