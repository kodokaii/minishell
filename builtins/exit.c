/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:10:08 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/08 14:20:20 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(char **argv)
{
	int	exit_code;

	exit_code = 0;
	if (*argv)
	{
		if (argv[1])
			return (ft_dprintf(STDERR_FILENO,
					PROGRAM_NAME": exit: too many arguments\n"), 0);
		exit_code = ft_atoi(*argv);
	}
	exit(exit_code);
	return (1);
}

