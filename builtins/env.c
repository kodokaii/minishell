/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:10:08 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/10 15:36:00 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **argv)
{
	t_list	*envp;

	envp = *ft_envp(NULL);
	if (*argv)
		return (ft_dprintf(STDERR_FILENO,
				PROGRAM_NAME": env: too many arguments\n"), 0);
	while (envp)
	{
		ft_putendl_fd((char *)envp->data, 1);
		envp = envp->next;
	}
	return (1);
}
