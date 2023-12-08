/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:53:07 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/08 14:24:00 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;
	char	**argv;

	while (1)
	{
		input = readline(PROGRAM_NAME"% ");
		if (input == NULL)
		{
			ft_putchar_fd('\n', 1);
			break ;
		}
		argv = ft_split(input, " \t");
		if (argv == NULL)
			return (free(input), 1);
		handle_builtins(argv);
		ft_split_free(argv);
		free(input);
	}
	return (0);
}
