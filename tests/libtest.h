/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libtest.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by cgodard           #+#    #+#             */
/*   Updated: 0000/00/00 00:00:00 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBTEST_H
# define LIBTEST_H

# include <stdio.h>
# include <regex.h>
# include <assert.h>
# include "libft.h"

void	assert_output(char **argv, char *expected_output);
void	assert_output_matches(char **argv, char *expected_output);
void	assert_error(char **argv, char *expected_output);
void	assert_error_matches(char **argv, char *expected_output);
void	assert_equal(char *s1, char *s2);

#endif
