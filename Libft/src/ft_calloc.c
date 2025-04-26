/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:38:34 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:02:21 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Allocates a quantity of memories and initializes with zeros
 * @param num Number of elements to allocate
 * @param size Size of every element in bytes
 * @return A pointer to ptr;
*/
void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;

	if (num == 0 || size == 0)
	{
		ptr = malloc(0);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	if ((num * size) / num != size)
		return (NULL);
	ptr = (void *)malloc(num * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, (num * size));
	return (ptr);
}
/*
int	main()
{
	int	*array = (int *)ft_calloc(5, sizeof(int));

	if (array == NULL)
	{
		printf("Erro: Falha ao alocar memória.\n");
		return (1);
	}
	free(array);

	return (0);
}
*/