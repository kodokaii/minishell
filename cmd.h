/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/15 17:55:09 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "libft/libft.h"

typedef enum e_control
{
	CONTROL_NONE,
	CONTROL_AND,
	CONTROL_OR,
}	t_control;

typedef struct s_cmd_list
{
	int			exit_code;
	t_control	control;
	t_list		*cmd;
}	t_cmd_list;

typedef enum e_ft
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
}	t_ft;

typedef struct s_file
{
	char	*name;
	t_ft	type;
}	t_file;

typedef struct s_cmd
{
	t_list		*files_in;
	char		**argv;
	pid_t		pid;
	int			exit_code;
	t_list		*files_out;
}				t_cmd;

#endif
