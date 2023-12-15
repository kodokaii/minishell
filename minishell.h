/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:53:07 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/15 03:40:36 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef PROGRAM_NAME
#  define PROGRAM_NAME "minishell"
# endif

# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "parsing/parsing.h"
# include "cmd.h"

typedef enum e_should_continue
{
	SHOULD_NOT_CONTINUE = 0,
	SHOULD_CONTINUE = 1,
}	t_should_continue;

typedef enum e_should_free
{
	SHOULD_NOT_FREE = 0,
	SHOULD_FREE = 1,
}	t_should_free;

// signals.c
void	setup_signals(void);

// env.c
t_list	**ft_envp(char **envp);
void	ft_unsetenv(char *name);
char	*ft_getenv(char *name);
void	ft_setenv(char *variable);

// builtins/
int		valid_builtin(char *name);
int		handle_builtins(char **argv, int fd);
int		builtin_cd(char **argv, int fd);
int		builtin_pwd(char **argv, int fd);
int		builtin_exit(char **argv, int fd);
int		builtin_env(char **argv, int fd);
int		builtin_echo(char **argv, int fd);
int		builtin_unset(char **argv, int fd);
int		builtin_export(char **argv, int fd);

// execution
int		ft_last_exit_code(int exit_code);
void	execution(t_list *command_line);
void	command_not_found(t_cmd *cmd);
void	get_envp_tab(char ***envp_tab);

#endif
