/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:11:51 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/10 15:22:49 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstremove(t_list **lst, t_list *to_remove, void (*del)(void *))
{
	t_list	*mylst;

	if (lst == NULL || to_remove == NULL)
		return ;
	if (*lst && *lst == to_remove)
	{
		*lst = (*lst)->next;
		del(to_remove->data);
		free(to_remove);
		return ;
	}
	mylst = *lst;
	while (mylst->next)
	{
		if (mylst->next == to_remove)
		{
			mylst->next = to_remove->next;
			del(to_remove->data);
			free(to_remove);
			break ;
		}
		mylst = mylst->next;
	}
}
