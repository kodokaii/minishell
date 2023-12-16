/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 03:44:14 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/16 03:17:00 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_should_continue	handle_input(char *input, t_should_free should_free)
{
	char	**argv;
	t_list	*command_line;

	if (input == NULL)
		return (ft_putchar_fd('\n', 1), SHOULD_NOT_CONTINUE);
	argv = ft_split(input, " \t");
	if (argv == NULL)
		return (free(input), SHOULD_NOT_CONTINUE);
	add_history(input);
	command_line = parse(input);
	if (0)
		ft_putlst_fd(command_line, print_cmd_list, STDOUT_FILENO);
	execution(command_line);
	ft_lstclear(&command_line, free_cmd_list);
	if (should_free)
		free(input);
	ft_split_free(argv);
	return (SHOULD_CONTINUE);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	ft_envp(envp);
	ft_argv(argv);
	if (argc == 2)
		return (handle_input(argv[1], SHOULD_NOT_FREE),
			ft_lstclear(ft_envp(NULL), free), ft_last_exit_code(-1));
	else if (argc > 2)
		return (ft_dprintf(STDERR_FILENO,
				PROGRAM_NAME": too many arguments\n"), 0);
	setup_signals();
	while (1)
	{
		input = readline("\033[1;32m"PROGRAM_NAME"\033[0m% ");
		if (!handle_input(input, SHOULD_FREE))
			break ;
	}
	ft_lstclear(ft_envp(NULL), free);
	return (ft_last_exit_code(-1));
}
