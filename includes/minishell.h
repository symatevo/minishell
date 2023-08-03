/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihovhann <ihovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:17:00 by ihovhann          #+#    #+#             */
/*   Updated: 2022/07/22 14:26:44 by ihovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef struct s_var
{
	char			*name;
	char			*value;
	char			meaning;
	int				status;
	struct s_var	*next;
}					t_var;

typedef struct s_token
{
	char			type;
	char			*value;
	char			*quote;
	struct s_token	*next;
}					t_token;

typedef struct s_command
{
	int					id;
	char				**args;
	char				*path;
	int					path_error;
	char				*oper;
	char				*oper_value;
	char				delimitor;
	int					builtin;
	int					std_in;
	int					std_in_dup1;
	int					std_out;
	int					std_out_dup1;
	int					std_err;
	int					pipe;
	int					pipe_out;
	int					pipe_in;
	struct s_command	*next;
}						t_command;

t_var		*lst_new_elem(char *name, char *value);
t_var		*lst_last(t_var *lst);
void		lst_add_back(t_var **lst, t_var *new_node);
void		lst_add_front(t_var **lst, t_var *new_elem);
void		lst_delone(t_var *lst, void (*del)(void *));
void		lst_clear(t_var **lst, void (*del)(void *));
int			lst_size(t_var *lst);

t_token		*lst_new_elem_token(char type, char *value);
t_token		*lst_last_token(t_token *lst);
void		lst_add_back_token(t_token **lst, t_token *new_node);
void		lst_delone_token(t_token *lst, void (*del)(void *));
void		lst_clear_token(t_token **lst, void (*del)(void *));
int			lst_size_token(t_token *lst);

void		signals_init(void);
void		handle_sigint_heredoc(int sig);

void		shlvl(t_var **env_lst);
int			env_to_list(char **envp, t_var **env_lst);
void		change_status(t_var **env_lst, int status);
char		**env_lst_to_arr(t_var *env_lst, char meaning, int quote);
char		*strjoin_base(char const *s1, char const *s2, char c);
void		arr_free(char **arr);

int			parsing_line(char *line, t_token **tokens, t_var **env_lst);
int			tokens_count(char *line, char *metachars);
void		tokens_array(char *line, char *metachars, t_token **tokens);
void		tokens_trim(t_token **tokens);
int			parsing_command(t_token **tokens, t_command *command, \
			t_var **env_lst);
void		quote_counting(t_token *tokens);
void		p_expansion(t_token *tokens, t_var *env_lst);
void		quote_removal(t_token *tokens);
void		word_splitting(t_token **tokens, t_var *env_lst);
int			operators(t_token *tokens);
int			arg_count(t_token **tokens, t_command *command);
int			parsing_opers(t_token **tokens, t_command *command, \
		t_var **env_lst);
int			tokens_to_struct(t_token **tokens, t_command **command, \
		t_var **env_lst);
int			heredoc(t_command *command, t_var **env_lst);
void		command_free(t_command *command);

char		*find_command(t_command *command, t_var *env_lst);
void		exec(t_command **command, t_var **env_lst);
void		execute_builtin(t_command *command,
				t_var **env_lst, int child_parent);
void		child(t_command **command, t_var **env_lst, int id);
void		dups(t_command *tmp);
int			pwd(t_var **env_lst);
int			env(t_var **env_lst);
int			unset(t_command *command, t_var **env_lst);
int			export_env(t_command *command, t_var **env_lst);
int			check_var_name(char *str, int *res, t_var **env_lst);
int			echo(t_command *command, t_var **env_lst);
int			my_exit(t_command *command, t_var **env_lst);
int			cd(t_command *command, t_var **env_lst);
int			change_dir(char *path, t_var **env_lst);

#endif
