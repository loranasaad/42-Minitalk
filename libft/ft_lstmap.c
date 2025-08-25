/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:29:15 by loasaad           #+#    #+#             */
/*   Updated: 2025/05/26 10:43:41 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list_new;
	t_list	*node_new;
	void	*content_new;

	if (!lst || !f)
		return (NULL);
	list_new = NULL;
	while (lst)
	{
		content_new = f(lst->content);
		node_new = ft_lstnew(content_new);
		if (!node_new)
		{
			del(content_new);
			ft_lstclear(&list_new, del);
			return (NULL);
		}
		ft_lstadd_back(&list_new, node_new);
		lst = lst->next;
	}
	return (list_new);
}
