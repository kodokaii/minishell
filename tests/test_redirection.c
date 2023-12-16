/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/16 04:00:22 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <assert.h>
#include "libtest.h"

int	main(void)
{
	ENSURE_OUTPUT(
		ARGV({"./minishell", "rm -f /tmp/minishell_test &&"
		   "echo hello > /tmp/minishell_test && cat /tmp/minishell_test", NULL}),
		"hello\n");

	ENSURE_OUTPUT(
		ARGV({"./minishell", "rm -f /tmp/minishell_test &&"
			"echo hello > /tmp/minishell_test && cat < /tmp/minishell_test", NULL}),
		"hello\n");

	ENSURE_OUTPUT(
		ARGV({"./minishell", "rm -f /tmp/minishell_test &&"
			"echo hello > /tmp/none > /tmp/minishell_test && cat /tmp/none /tmp/minishell_test", NULL}),
		"hello\n");

	ENSURE_OUTPUT(
		ARGV({"./minishell", "rm -f /tmp/minishell_test &&"
			"echo hello > /tmp/minishell_test | cat", NULL}),
		NULL);

	ENSURE_OUTPUT(
		ARGV({"./minishell", "echo hello > kdwlefjsldjlk | echo world", NULL}),
		"world\n");

	ENSURE_OUTPUT(
		ARGV({"./minishell", "echo hello > kdwlefjsldjlk < minishell | echo world", NULL}),
		"world\n");

	ENSURE_OUTPUT(
		ARGV({"./minishell", "echo hello > kdwlefjsldjlk > /dev/null | echo world", NULL}),
		"world\n");
}
