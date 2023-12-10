/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:58:18 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/08 19:06:37 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **argv)
{
	int		output_newline;
	size_t	i;

	i = 1;
	output_newline = 1;
	if (*argv && **argv == '-')
	{
		while ((*argv)[i] == 'n')
			++i;
		if (i != 1 && (*argv)[i] == 0)
		{
			output_newline = 0;
			++argv;
		}
	}
	while (*argv)
	{
		ft_putstr_fd(*argv++, 1);
		if (*argv)
			ft_putchar_fd(' ', 1);
	}
	if (output_newline)
		ft_putchar_fd('\n', 1);
	return (1);
}
