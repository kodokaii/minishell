/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:41:53 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/15 03:35:11 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <assert.h>
#include "minishell.h"
#include "libtest.h"

#define FAILING_TEST(cmdline)                 \
	{                                         \
		/* redirect errors to /dev/null */    \
		int	o = dup(2);                       \
		int	fd = open("/dev/null", O_RDONLY); \
		dup2(fd, 2);                          \
		assert(parse(cmdline) == NULL);       \
		dup2(o, 2);                           \
	}

#define TEST_CASE(cmdline, code)                    \
	{                                               \
		/* we save a copy of argv so we can         \
		 * increment it and it looks cooler */      \
		t_list		*command_line = parse(cmdline); \
		t_list		*root = command_line;           \
		t_cmd_list	*cmd_list = command_line->data; \
		t_list		*cmd_copy = cmd_list->cmd;      \
		t_cmd		*cmd = cmd_list->cmd->data;     \
		                                            \
		char	**argv = cmd->argv;                 \
		code;                                       \
		cmd->argv = argv;                           \
		((t_cmd_list *)root->data)->cmd = cmd_copy; \
		ft_lstclear(&root, free_cmd_list);          \
	}

#define NEXT_CMD() \
		cmd->argv = argv; \
		cmd_list->cmd = cmd_list->cmd->next; \
		cmd = cmd_list->cmd->data; \
		argv = cmd->argv;

#define NEXT_CMD_LIST() \
		cmd->argv = argv; \
		command_line = command_line->next; \
		cmd_list = command_line->data; \
		cmd = cmd_list->cmd->data; \
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
		NEXT_CMD_LIST();
		assert_equal(*cmd->argv++, "ls");
		assert(command_line->next == NULL);
	})

	TEST_CASE("echo     hello || ls", {
		assert_equal(*cmd->argv++, "echo");
		assert_equal(*cmd->argv++, "hello");
		assert(cmd->fd_in == STDIN_FILENO);
		assert(*cmd->argv == NULL);
		NEXT_CMD_LIST();
		assert_equal(*cmd->argv++, "ls");
		assert(cmd->fd_out == STDOUT_FILENO);
		assert(command_line->next == NULL);
	})

	TEST_CASE("echo   owo| false|| ls", {
		assert_equal(*cmd->argv++, "echo");
		assert_equal(*cmd->argv++, "owo");
		assert(*cmd->argv == NULL);
		NEXT_CMD();
		assert_equal(*cmd->argv++, "false");
		assert(*cmd->argv == NULL);
		NEXT_CMD_LIST();
		assert_equal(*cmd->argv++, "ls");
		assert(*cmd->argv == NULL);
		assert(cmd->fd_out == STDOUT_FILENO);
		assert(command_line->next == NULL);
	})

	FAILING_TEST("echo   owo| false| | ls");
	FAILING_TEST("echo   owo| false|&& | ls");
	FAILING_TEST("echo   owo| false&& | ls");
	FAILING_TEST("echo   owo| false&& |");
	FAILING_TEST("|");
	FAILING_TEST("&&&&");
	FAILING_TEST("|||&");
	FAILING_TEST("echo|");
	FAILING_TEST("|echo|");
	//FAILING_TEST("echo (world)");
	//FAILING_TEST("echo (");
}
