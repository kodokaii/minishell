/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:53:07 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/11 11:14:39 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_should_continue	handle_input(char *input, t_should_free should_free)
{
	char	**argv;

	if (input == NULL)
		return (ft_putchar_fd('\n', 1), SHOULD_NOT_CONTINUE);
	argv = ft_split(input, " \t");
	if (argv == NULL)
		return (free(input), SHOULD_NOT_CONTINUE);
	add_history(input);
	handle_builtins(argv);
	parsing(input);
	if (should_free)
		free(input);
	ft_split_free(argv);
	return (SHOULD_CONTINUE);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	ft_envp(envp);
	if (argc == 2)
		return (handle_input(argv[1], SHOULD_NOT_FREE),
			ft_lstclear(ft_envp(NULL), free), 0);
	else if (argc > 2)
		return (ft_dprintf(STDERR_FILENO,
				PROGRAM_NAME": too many arguments\n"), 0);
	setup_signals();
	while (1)
	{
		input = readline(PROGRAM_NAME"% ");
		if (!handle_input(input, SHOULD_FREE))
			break ;
	}
	ft_lstclear(ft_envp(NULL), free);
	return (0);
}
