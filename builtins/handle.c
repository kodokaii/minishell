/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:55:20 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/15 03:40:43 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_builtin(char *name)
{
	return (ft_strcmp(name, "cd") == 0
		|| ft_strcmp(name, "pwd") == 0
		|| ft_strcmp(name, "exit") == 0
		|| ft_strcmp(name, "env") == 0
		|| ft_strcmp(name, "echo") == 0
		|| ft_strcmp(name, "unset") == 0
		|| ft_strcmp(name, "export") == 0);
}

int	handle_builtins(char **argv, int fd)
{
	if (*argv == NULL)
		return (1);
	if (ft_strcmp(*argv, "cd") == 0)
		return (builtin_cd(argv + 1, fd));
	else if (ft_strcmp(*argv, "pwd") == 0)
		return (builtin_pwd(argv + 1, fd));
	else if (ft_strcmp(*argv, "exit") == 0)
		return (builtin_exit(argv + 1, fd));
	else if (ft_strcmp(*argv, "env") == 0)
		return (builtin_env(argv + 1, fd));
	else if (ft_strcmp(*argv, "echo") == 0)
		return (builtin_echo(argv + 1, fd));
	else if (ft_strcmp(*argv, "unset") == 0)
		return (builtin_unset(argv + 1, fd));
	else if (ft_strcmp(*argv, "export") == 0)
		return (builtin_export(argv + 1, fd));
	return (1);
}
