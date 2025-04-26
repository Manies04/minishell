/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:54:02 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:05:08 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Concatenar as strings
 * @param content If character is uppercase, puts it in lowercase
 * @param dest Destination of the concatenation 
 * @param src Source of the concatenation
 * @param len Size of the concatenation
 * @return The lenght of the str
*/
size_t	ft_strlcat(char *dest, const char *src, size_t len)
{
	size_t	srclen;
	size_t	destlen;
	size_t	i;

	srclen = ft_strlen(src);
	destlen = ft_strlen(dest);
	i = 0;
	if (len <= destlen)
		return (srclen + len);
	while (src[i] && (destlen + i) < (len - 1))
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (destlen + srclen);
}
