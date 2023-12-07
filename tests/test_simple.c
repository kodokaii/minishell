/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by cgodard           #+#    #+#             */
/*   Updated: 0000/00/00 00:00:00 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "libtest.h"

#define	ARGV(...) __VA_ARGS__
#define ENSURE_OUTPUT(argv, output)           \
{                                             \
    char    *__argv[] = argv;                 \
    assert_output_matches(__argv, output);    \
}

int	main(void)
{
	ENSURE_OUTPUT(
		ARGV({"./minishell", NULL}),
		"Project written by .+ le goat\n");
}
