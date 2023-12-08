/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:35:31 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/08 14:39:50 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char *const	*ft_envp(char *const *envp)
{
	static char	*const *saved_envp = NULL;

	if (envp == NULL)
		return (saved_envp);
	saved_envp = envp;
	return (NULL);
}
