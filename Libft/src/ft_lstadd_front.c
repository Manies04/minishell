/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:46:52 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:03:17 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Adds a new node at the beggining
 * @param **lst Pointer to Pointer to the first element of the list
 * @param *new Pointer to the new element
 * @return Nothing
*/
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		new->next = *lst;
		*lst = new;
	}
}
/*int	main()
{
	t_list	*node1;
	t_list	*node2;
	t_list	*current;

	node1 = ft_lstnew("alo");
	node2 = ft_lstnew("ola");
	ft_lstadd_front(&node2, node1);

	current = node1;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	free(node1);
	free(node2);
	return (0);
}*/