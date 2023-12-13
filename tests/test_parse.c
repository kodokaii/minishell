/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:41:53 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/13 10:25:36 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <assert.h>
#include "minishell.h"
#include "libtest.h"

#define TEST_CASE(cmdline, code)                \
	{                                           \
		/* we save a copy of argv so we can     \
		 * increment it and it looks cooler */  \
		t_list	*command_line = parse(cmdline); \
		t_list	*root = command_line;           \
		t_cmd	*cmd = command_line->data;      \
		char	**argv = cmd->argv;             \
		code;                                   \
		cmd->argv = argv;                       \
		ft_lstclear(&root, free_cmd);   \
	}

#define NEXT_CMD() \
		cmd->argv = argv; \
		command_line = command_line->next; \
		cmd = command_line->data; \
		argv = cmd->argv;

int	main(void)
{
	TEST_CASE("echo", {
		assert_equal(*cmd->argv++, "echo");
		assert(*cmd->argv == NULL);
		assert(command_line->next == NULL);
	})

	TEST_CASE("echo hello", {
		assert_equal(*cmd->argv++, "echo");
		assert_equal(*cmd->argv++, "hello");
		assert(*cmd->argv == NULL);
		assert(command_line->next == NULL);
	})

	TEST_CASE("echo     hello", {
		assert_equal(*cmd->argv++, "echo");
		assert_equal(*cmd->argv++, "hello");
		assert(*cmd->argv == NULL);
		assert(command_line->next == NULL);
	})

	TEST_CASE("echo     hello |echo world", {
		assert_equal(*cmd->argv++, "echo");
		assert_equal(*cmd->argv++, "hello");
		assert(*cmd->argv == NULL);
		NEXT_CMD();
		assert_equal(*cmd->argv++, "echo");
		assert_equal(*cmd->argv++, "world");
		assert(command_line->next == NULL);
	})

	TEST_CASE("echo     hello &&	ls", {
		assert_equal(*cmd->argv++, "echo");
		assert_equal(*cmd->argv++, "hello");
		assert(*cmd->argv == NULL);
		NEXT_CMD();
		assert_equal(*cmd->argv++, "ls");
		assert(command_line->next == NULL);
	})

	TEST_CASE("echo     hello || ls", {
		assert_equal(*cmd->argv++, "echo");
		assert_equal(*cmd->argv++, "hello");
		assert(*cmd->argv == NULL);
		NEXT_CMD();
		assert_equal(*cmd->argv++, "ls");
		assert(command_line->next == NULL);
	})
}
