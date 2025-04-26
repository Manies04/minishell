/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:06:41 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:03:32 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Applies a certain function to every node
 * @param *lst Pointer to first element of the list
 * @param *f Pointer to function
 * @return Nothing
*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
void print(void *data)
{
	int *ptr = (int *)data;
	printf("%d\n", *ptr);
}
int main()
{
	t_list *node1 = malloc(sizeof(t_list));
	t_list *node2 = malloc(sizeof(t_list));
	t_list *node3 = malloc(sizeof(t_list));

	int num1 = 10, num2 = 20, num3 = 30;

	node1->content = &num1;
	node1->next = node2;

	node2->content = &num2;
	node2->next = node3;

	node3->content = &num3;
	node3->next = NULL;

	ft_lstiter(node1, &print);

	free(node1);
	free(node2);
	free(node3);
	return (0);
}
*/