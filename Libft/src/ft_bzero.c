/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:57:49 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:02:18 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Erase the data in n bytes of memorie
 * @param *a Pointer to a memory block
 * @param n Size of bytes
 * @return None
*/
void	ft_bzero(void *a, size_t n)
{
	char	*i;

	i = (char *)a;
	while (n != 0)
	{
		*i = 0;
		i++;
		n--;
	}
}
/*int	main()
{
	char	buffer[10];
	strcpy(buffer, "abcdefg");
	printf("Antes do ft_bzero : %s\n", buffer);
	ft_bzero(buffer, sizeof(buffer));
	printf("Depois do ft_bzero: %s\n", buffer);
	return (0);
}*/