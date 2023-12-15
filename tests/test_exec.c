/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/15 04:19:50 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <assert.h>
#include "libtest.h"

int	main(void)
{
	ENSURE_OUTPUT(
		ARGV({"./minishell", "printf yoyoy", NULL}),
		"yoyoy");

	ENSURE_OUTPUT(
		ARGV({"./minishell", "printf yoyoy |wc -c", NULL}),
		"5\n");

	ENSURE_OUTPUT(
		ARGV({"./minishell", "true && printf yoyoy |wc -c", NULL}),
		"5\n");

	ENSURE_OUTPUT(
		ARGV({"./minishell", "false && printf yoyoy |wc -c", NULL}),
		NULL);

	ENSURE_OUTPUT(
		ARGV({"./minishell", "(false)", NULL}),
		NULL);

	ENSURE_OUTPUT(
		ARGV({"./minishell", "false|| printf yoyoy |wc -c", NULL}),
		"5\n");

	ENSURE_OUTPUT(
		ARGV({"./minishell", "false || (printf yoyoy |wc -c)", NULL}),
		"5\n");

	ENSURE_OUTPUT(
		ARGV({"./minishell", "(false )|| (printf yoyoy |wc -c)", NULL}),
		"5\n");
}
