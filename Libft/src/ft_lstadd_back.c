/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:05:52 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:02:53 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Adds a new node in the back of the list
 * @param **lst Pointer to Pointer to the first element of the list
 * @param *new Pointer to the new element
 * @return Nothing
*/
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}

/*int main()
{
	t_list	*list = NULL;
	t_list	*node1;
	t_list	*node2;
	
	node1 = ft_lstnew("node1");
	node2 = ft_lstnew("node2");
	ft_lstadd_back(&list, node1);
	ft_lstadd_back(&list, node2);
	printf("Conteúdos da lista:\n");
	t_list *current = list;
	while (current != NULL)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	while (list != NULL)
	{
		t_list *temp = list;
		list = list->next;
		free(temp);
	}
	return (0);
}*/
