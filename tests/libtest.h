/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libtest.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/10 16:51:10 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBTEST_H
# define LIBTEST_H

# include <stdio.h>
# include <regex.h>
# include <assert.h>
# include "libft.h"

#define	ARGV(...) __VA_ARGS__

#define ENSURE_OUTPUT(argv, output) \
{                                   \
    char    *__argv[] = argv;       \
    assert_output(__argv, output);  \
}

#define ENSURE_ERROR(argv, output) \
{                                  \
    char    *__argv[] = argv;      \
    assert_error(__argv, output);  \
}

#define ENSURE_OUTPUT_MATCHES(argv, output) \
{                                           \
    char    *__argv[] = argv;               \
    assert_output_matches(__argv, output);  \
}

#define ENSURE_ERROR_MATCHES(argv, output) \
{                                          \
    char    *__argv[] = argv;              \
    assert_error_matches(__argv, output);  \
}

void	assert_output(char **argv, char *expected_output);
void	assert_output_matches(char **argv, char *expected_output);
void	assert_error(char **argv, char *expected_output);
void	assert_error_matches(char **argv, char *expected_output);
void	assert_equal(char *s1, char *s2);

#endif
