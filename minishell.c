/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:32:10 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/13 22:28:53 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	ft_printf("argv: ");
	while (cmd->argv[i])
		ft_printf("%s ", cmd->argv[i++]);
	ft_printf("\nfd in: %d\nfd out: %d\n", cmd->fd_in, cmd->fd_out);
}

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
	handle_builtins(argv);
	command_line = parse(input);
	ft_lstclear(&command_line, free_cmd);
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
