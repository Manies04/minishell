/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:07:09 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:03:47 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Applies the function f to each node, if needed use delete
 * @param *lst Pointer to a node
 * @param *f Pointer to the function we will use
 * @param *del Pointer of the function to delete
 * @return The new list that was created
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*b;

	if (!lst || !f)
		return (NULL);
	new = NULL;
	while (lst)
	{
		b = ft_lstnew(f(lst->content));
		if (!b)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, b);
		lst = lst->next;
	}
	return (new);
}
