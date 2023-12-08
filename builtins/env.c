/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:10:08 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/08 14:45:15 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **argv)
{
	char *const	*envp;

	envp = ft_envp(NULL);
	if (*argv)
		return (ft_dprintf(STDERR_FILENO,
				PROGRAM_NAME": env: too many arguments\n"), 0);
	while (*envp)
		ft_putendl_fd(*envp++, 1);
	return (1);
}
