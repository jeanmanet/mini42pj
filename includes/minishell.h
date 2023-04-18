/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:09:47 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/18 21:04:38 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_lst_var
{
	char			*name;
	char			*value;
	int			flag_var_for_env;
	struct	s_lst_var 	*previous;
	struct	s_lst_var 	*next;
}	t_lst_var;

typedef struct s_global	
{
    int 	g_pid;
    int		fd_here_doc;
    int		tmp_fd_here_doc;
    int		exit_code;
}	t_global;

extern t_global global;

enum	e_lexer_type{
	LEX_WORD,
	LEX_SMALLER,
	LEX_GREATER,
	LEX_PIPE,
	LEX_SQUOTE,
	LEX_DQUOTE,
	LEX_SPACE
};

enum	e_cmd_io{
	CMD_STDIN,
	CMD_STDOUT,
	CMD_INFILE,
	CMD_HERE_DOC,
	CMD_APPEND,
	CMD_TRUNC
};

enum	e_token_state{
	S_IN_SQUOTE,
	S_IN_DQUOTE,
	S_NOT_IN_QUOTE
};

enum	e_token_type{
	T_ARG,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_VAR,
	T_PIPE
};

enum	e_ast_node_type{
	AST_CMD,
	AST_PIPE
};

typedef struct s_token_node{
	char				*token;
	int					q_state;
	int					type;
	struct s_token_node	*next;
	struct s_token_node	*prev;
}t_token_node;

typedef struct s_com
{
	char	**args;
	char	*infile;
	char	*outfile;
	char	*here_doc_limiter;
	int		cmd_input_mode;
	int		cmd_output_mode;
}t_com;

typedef struct s_ast_node	t_ast_node;

typedef struct s_pipe
{
	t_ast_node	*left;
	t_ast_node	*right;
}t_pipe;

typedef union u_union
{
	t_pipe	*pipe;
	t_com	*cmd;
}t_union;

typedef struct s_ast_node
{
	enum e_ast_node_type	type;
	t_union					*content;
}t_ast_node;

typedef struct s_ast
{
	t_ast_node	*root;
}	t_ast;

typedef struct s_data
{
	t_token_node	*token_list;
	t_ast			*commands_tree;
	char			*command_line;
	char			**envp;
	int				endstatus;
	t_lst_var 	*var_list;
	pid_t			pid;

}	t_data;

char			*get_absolute_command(char	*arg, char **envp);
char			**ft_import_envp(char **envp);
char			*ft_getenv(char *name, t_data *data);
int				ft_setenv(char *name, char *value, int overwrite, t_data *data, int flag_plus);
int				ft_change_directory(t_com *command, t_data *data);
int				exec_command(t_com *command, t_data *data);
int				exec_processus(t_com *command, t_data *data);
int				cmd_is_builtin(t_com *command);
int				exec_builtin(t_com *command, t_data *data);
void			exit_cmd_strerror(char *cmd_name);
void			cmd_not_found(char *cmd_name);
void			ft_exit_error(char *error_msg);
int				ft_redirect_io(t_com *command);
int				open_infile(t_data *data);
int				open_outfile(t_data *data);
void			parse_token_list(t_data *data);
int				ft_lexing(char c);
int				execute_ast(t_data *data);
t_token_node	*create_token_node(char *token, int state);
void			add_token_node(t_token_node **list_head,
					char *token, int state);
void			print_tokens(t_token_node *list_head);
t_token_node	*tokenizer(char *commandline);
void			add_ast_node(t_data *data, t_union *content, int type);
void			free_mem(t_data *data);
t_union			*init_cmd_union(t_com *command);
t_union			*init_pipe_union(void);
void			rl_replace_line(const char *text, int clear_undo);

void	handle_sigint(void);
void	handle_sigquit(void);
void	ft_sigaction(int signal);
void	ft_signal_handler(void);
void	ft_signal_handler_here_doc(int signal);

void rl_replace_line (const char *, int);

void lst_add_var(t_data *data, char *name, char *value, int flag);
t_lst_var       *ft_var_lstnew(char *name, char *value, int flag);
void	ft_var_lstadd_back(t_lst_var **lst, t_lst_var *new);
t_lst_var	*ft_var_lstlast(t_lst_var *lst);
void delete_var_lst(t_lst_var **head, t_lst_var *to_delete);
void    delete_var_in_lst(t_lst_var **head, char *name);
void	delete_var_in_env(char *name, t_data *data);


int	ft_env(t_data *data);
int	ft_unset(t_com *command, t_data *data);
int	unexpected_token(char *command_line);
int	unexpected_token_2(t_data *data);
int	is_only_compose_by_redir_char(char *str);
int	str_is_only_this_char(char *str, int c);

void	ft_command_line(t_data *data);

char	*var_exist_outside_env(t_data *data, char *var_name);
int	replace_var_by_value(t_data *data);
void	add_var_in_list(t_data *data, char *str);
char 	*get_env_variable_value(char *var_name, t_data *data);
void	ft_str_replace(char **str, int start, char *value);
int	check_if_var_is_for_env(char *name, char *value, t_data *data, int flag_plus);
int	var_is_in_env(char *name, t_data *data);
int	unexpected_char_in_name(char *str);
char	*extract_value_in_assignment(char *str);
char	*extract_name_in_assignment(char *str);
char	*var_name(char *str, int flag);

char	*replace_var(char *var, t_data *data);
char* extract_vars(char* str, t_data *data);
int	cmd_is_builtin_2(char *command);
char	*str_is_cmd(char	*arg, char **envp);
#endif
