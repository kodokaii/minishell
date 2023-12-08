/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:53:07 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/08 14:14:25 by cgodard          ###   ########.fr       */
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
# include <readline/readline.h>
# include "libft.h"

// builtins
int	handle_builtins(char **argv);
int	builtin_cd(char **argv);
int	builtin_pwd(char **pwd);
int	builtin_exit(char **pwd);

#endif
