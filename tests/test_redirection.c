/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/15 17:34:21 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <assert.h>
#include "libtest.h"

int	main(void)
{
	printf("test 1\n");
	ENSURE_OUTPUT(
		ARGV({"./minishell", "rm -f /tmp/minishell_test &&"
		   "echo hello > /tmp/minishell_test && cat /tmp/minishell_test", NULL}),
		"hello");

	printf("test 2\n");
	ENSURE_OUTPUT(
		ARGV({"./minishell", "rm -f /tmp/minishell_test &&"
			"echo hello > /tmp/minishell_test && cat < /tmp/minishell_test", NULL}),
		"hello");

	printf("test 3\n");
	ENSURE_OUTPUT(
		ARGV({"./minishell", "rm -f /tmp/minishell_test &&"
			"echo hello > /tmp/none > /tmp/minishell_test && cat /tmp/none /tmp/minishell_test", NULL}),
		"hello");

	printf("test 4\n");
	ENSURE_OUTPUT(
		ARGV({"./minishell", "rm -f /tmp/minishell_test &&"
			"echo hello > /tmp/minishell_test | cat", NULL}),
		NULL);
}
