/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:10:08 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/15 03:43:22 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char **argv, int fd)
{
	char	*pwd;

	if (*argv)
		return (ft_dprintf(STDERR_FILENO,
				PROGRAM_NAME": pwd: too many arguments\n"), 1);
	pwd = getcwd(NULL, PATH_MAX);
	ft_putendl_fd(pwd, fd);
	free(pwd);
	return (0);
}
