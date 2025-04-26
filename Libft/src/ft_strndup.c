/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:21:39 by joaoleote         #+#    #+#             */
/*   Updated: 2025/04/23 15:05:29 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Allocates a new string suplicated by 'src'
 * @param *src Pointer to a string that will be duplicated
 * @return A new string duplicated by 'src'
*/
char	*ft_strndup(char const *src, unsigned int n)
{
	char			*dup;
	unsigned int	index;

	index = 0;
	if (!src || n == 0)
		return (NULL);
	dup = malloc(sizeof(char) * (n + 1));
	if (dup == NULL)
		return (NULL);
	while (src[index] && index < n)
	{
		dup[index] = src[index];
		index++;
	}
	dup[index] = '\0';
	return (dup);
}
