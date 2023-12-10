/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/09 19:29:11 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <assert.h>
#include "libtest.h"

#define	ARGV(...) __VA_ARGS__
#define ENSURE_OUTPUT(argv, output) \
{                                   \
    char    *__argv[] = argv;       \
    assert_output(__argv, output);  \
}

int	main(void)
{
	ENSURE_OUTPUT(
		ARGV({"./minishell", "echo hello", NULL}),
		"hello\n");

	ENSURE_OUTPUT(
		ARGV({"./minishell", "echo", NULL}),
		"\n");

	ENSURE_OUTPUT(
		ARGV({"./minishell", "echo -n hello", NULL}),
		"hello");

	ENSURE_OUTPUT(
		ARGV({"./minishell", "echo -nnnnnnnn hello", NULL}),
		"hello");

	ENSURE_OUTPUT(
		ARGV({"./minishell", "echo -nnnnnnnn hello world", NULL}),
		"hello world");

	ENSURE_OUTPUT(
		ARGV({"./minishell", "echo hello     world", NULL}),
		"hello world\n");
}