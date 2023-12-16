/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exit_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/16 03:38:32 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <assert.h>
#include "libtest.h"

int	main(void)
{
	ENSURE_OUTPUT(
		ARGV({"./minishell", "echo $?", NULL}),
		"0\n");

	ENSURE_OUTPUT(
		ARGV({"./minishell", "false || echo $?", NULL}),
		"1\n");

	ENSURE_OUTPUT(
		ARGV({"./minishell", "true && echo $?", NULL}),
		"0\n");
}
