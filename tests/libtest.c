/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libtest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/12 23:20:12 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtest.h"

static size_t	count_newlines(char *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			++j;
		++i;
	}
	if (s[i] != '\n')
		++j;
	return (j);
}

static char	**split(char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	len;
	char	**result;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	len = ft_strlen(s);
	result = malloc((count_newlines(s) + 1) * sizeof(char *));
	while (i < len + 1)
	{
		if (s[i] == c || (s[i] == 0 && j + 1 != i))
		{
			result[k] = malloc(i - j + 2);
			ft_strlcpy(result[k], s + j, i - j + 2);
			++k;
			j = i;
		}
		++i;
	}
	result[k] = NULL;
	return (result);
}

static void	tell_if_has_no_more_output(char **s)
{
	if (*s == NULL)
		*s = ft_strdup("(no more output)");
}

static void	error_out(char *s1, char *s2,
	char **parts, int pipefd[2], int does_regex)
{
	int		has_freed_s1;
	size_t	i;

	ft_putstr_fd("Output does not match!\n", 2);
	if (does_regex)
		ft_putstr_fd("Expected to match:\n", 2);
	else
		ft_putstr_fd("Expected:\n", 2);
	ft_putstr_fd(s1, 2);
	if (s1[ft_strlen(s1) - 1] != '\n')
		ft_putchar_fd('\n', 2);
	ft_putstr_fd("Got:\n", 2);
	ft_putstr_fd(s2, 2);
	if (s2[ft_strlen(s2) - 1] != '\n')
		ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);
	i = 0;
	has_freed_s1 = 0;
	while (parts[i])
	{
		if (s1 == parts[i])
			has_freed_s1 = 1;
		free(parts[i]);
		++i;
	}
	free(parts);
	if (!has_freed_s1)
		free(s1);
	ft_close(&pipefd[0]);
	free(s2);
	exit(1);
}

static void	child_proc(int pipefd[2], char **argv, int fd)
{
	close(pipefd[0]);
	dup2(pipefd[1], fd);
	if (execve(*argv, argv, NULL) < 0)
	{
		perror("execve");
		exit(1);
	}
}

int	cmp(char *s1, char *s2)
{
	if (s1 == NULL && s2)
		return (1);
	if (s1 && s2 == NULL)
		return (1);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	return (ft_strcmp(s1, s2));
}

static void	parent_proc(int pipefd[2], char **parts, int do_regex)
{
	char	*s1;
	char	*s2;
	regex_t	regex;
	size_t	i;

	i = 0;
	s2 = NULL;
	close(pipefd[1]);
	wait(NULL);
	while (1)
	{
		if (parts == NULL)
			s1 = NULL;
		else
			s1 = parts[i];
		if (s2)
			free(s2);
		s2 = ft_gnl(pipefd[0]).buf;
		if (s1 == NULL && s2 == NULL)
			break ;
		tell_if_has_no_more_output(&s1);
		tell_if_has_no_more_output(&s2);
		if (do_regex)
		{
			if (regcomp(&regex, s1, REG_EXTENDED))
			{
				perror("regcomp");
				exit(1);
			}
			if (regexec(&regex, s2, 0, NULL, 0) != 0)
			{
				regfree(&regex);
				error_out(s1, s2, parts, pipefd, do_regex);
			}
			regfree(&regex);
		}
		else if (cmp(s1, s2) != 0)
			error_out(s1, s2, parts, pipefd, do_regex);
		++i;
	}
	ft_split_free(parts);
	free(s2);
}

void	assert_output(char **argv, char *expected_output)
{
	char	**parts;
	int		pipefd[2];

	parts = split(expected_output, '\n');
	pipe(pipefd);
	if (fork() == 0)
		child_proc(pipefd, argv, 1);
	else
		parent_proc(pipefd, parts, 0);
}

void	assert_output_matches(char **argv, char *expected_output)
{
	char	**parts;
	int		pipefd[2];

	parts = split(expected_output, '\n');
	pipe(pipefd);
	if (fork() == 0)
		child_proc(pipefd, argv, 1);
	else
		parent_proc(pipefd, parts, 1);
}

void	assert_error(char **argv, char *expected_output)
{
	char	**parts;
	int		pipefd[2];

	parts = split(expected_output, '\n');
	pipe(pipefd);
	if (fork() == 0)
		child_proc(pipefd, argv, 2);
	else
		parent_proc(pipefd, parts, 0);
}

void	assert_error_matches(char **argv, char *expected_output)
{
	char	**parts;
	int		pipefd[2];

	parts = split(expected_output, '\n');
	pipe(pipefd);
	if (fork() == 0)
		child_proc(pipefd, argv, 2);
	else
		parent_proc(pipefd, parts, 1);
}

void	assert_equal(char *s1, char *s2)
{
	if (s1 == NULL || s2 == NULL)
		assert(s1 == s2);
	assert(ft_strcmp(s1, s2) == 0);
}

void	assert_nonequal(char *s1, char *s2)
{
	if (s1 == NULL || s2 == NULL)
		assert(s1 != s2);
	assert(ft_strcmp(s1, s2));
}
