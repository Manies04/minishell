/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:06:21 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:03:23 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Deletes one node and every node in front 
 * @param **lst Pointer to Pointer to the first element of the list
 * @param *del Pointer of the function to delete
 * @return Nothing
*/
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*i;

	if (!*lst)
		return ;
	while (*lst)
	{
		i = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = i;
	}
	*lst = 0;
}
/*
void	del(void *content)
{
	free(content);
}

int main()
{
	t_list *node1 = malloc(sizeof(t_list));
	node1->content = malloc(sizeof(int));
	*(int *)(node1->content) = 1;
	node1->next = NULL;

	t_list *node2 = malloc(sizeof(t_list));
	node2->content = malloc(sizeof(int));
	*(int *)(node2->content) = 2;
	node2->next = NULL;

	t_list *head = node1;
	node1->next = node2;
	ft_lstclear(&head, &del);
	if (head == NULL)
		printf("Lista limpa com sucesso!\n");
	else
		printf("Erro ao limpar a lista!\n");
	return (0);
}*/