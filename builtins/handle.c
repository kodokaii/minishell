/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:55:20 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/08 17:06:42 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_builtins(char **argv)
{
	if (*argv == NULL)
		return (0);
	if (ft_strcmp(*argv, "cd") == 0)
		return (builtin_cd(argv + 1), 1);
	else if (ft_strcmp(*argv, "pwd") == 0)
		return (builtin_pwd(argv + 1), 1);
	else if (ft_strcmp(*argv, "exit") == 0)
		return (builtin_exit(argv + 1), 1);
	else if (ft_strcmp(*argv, "env") == 0)
		return (builtin_env(argv + 1), 1);
	else if (ft_strcmp(*argv, "echo") == 0)
		return (builtin_echo(argv + 1), 1);
	else if (ft_strcmp(*argv, "unset") == 0)
		return (builtin_unset(argv + 1), 1);
	else if (ft_strcmp(*argv, "export") == 0)
		return (builtin_export(argv + 1), 1);
	return (0);
}
