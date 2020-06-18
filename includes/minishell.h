/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 19:41:53 by cclaude           #+#    #+#             */
/*   Updated: 2020/06/18 14:21:14 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
// # include <sys/types.h>
// # include <stdbool.h>
// # include <stdarg.h>

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

typedef struct	s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_mini
{
	t_token			*start;
	int				in;
	int				out;
	int				fdin;
	int				fdout;
	int				pipin;
	int				pipout;
	int				pid;
	t_env			*env;
	int				run;
}				t_mini;

/* MINISHELL */
void	redir(t_mini *mini, t_token *token, int type);
void	input(t_mini *mini, t_token *token);
int		minipipe(t_mini *mini);

/* EXEC */
void	exec_cmd(t_mini *mini, t_token *token);
int		exec_bin(char **args, t_env *env);
int		is_builtin(char	*command);
int		exec_builtin(char **args, t_env *env);

/* BUILTINS */
int		ft_echo(char **args);
int		ft_cd(char **args, t_env *env);
int		ft_pwd(void);
int		ft_export(char **args, t_env *env);
void	ft_env(t_env *env);

/* PARSING */
void	parse(t_mini *mini);
t_token	*get_tokens(char *line);
int		open_quotes(char *line, int index);
int		is_sep(char *line, int i);
int		ignore_sep(char *line, int i);

/* ENV */
int		env_init(t_mini *mini, char **env_array);
char	*env_to_str(t_env *lst);

/* FD TOOLS */
void	reset_std(t_mini *mini);
void	close_fds(t_mini *mini);
void	reset_fds(t_mini *mini);

/* FREE TOOLS */
void	free_token(t_token *start);
void	free_env(t_env *env);
void	free_tab(char **tab);

/* TOKEN TOOLS */
int		is_type(t_token *token, int type);
t_token	*next_type(t_token *token, int type, int skip);
t_token	*next_sep(t_token *token, int skip);
t_token	*prev_sep(t_token *token, int skip);
t_token	*next_run(t_token *token, int skip);

#endif
