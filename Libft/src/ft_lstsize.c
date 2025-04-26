/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:04:00 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:03:56 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Counts the number of nodes
 * @param *lst Pointer to the beggining of the list
 * @return The length of the list
*/
int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*ptr;

	count = 0;
	ptr = lst;
	while (ptr != NULL)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}
/*
int main()
{
	t_list *node1 = malloc(sizeof(t_list));
	t_list *node2 = malloc(sizeof(t_list));
	t_list *node3 = malloc(sizeof(t_list));

	node1->content = (void *)2;
	node1->next = NULL;
	node2->content = (void *)20;
	node2->next = node3;
	node3->content = (void *)30;
	node3->next = NULL;

	int size = ft_lstsize(node1);
	printf("Tamanho da lista: %d\n", 2);

	free(node1);
	free(node2);
	free(node3);
	return (0);
}*/
