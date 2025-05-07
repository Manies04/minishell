/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 01:45:44 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/07 01:46:14 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**@brief This function duplicates the first 'n' characters of a string.
 * @param s1 The string to duplicate
 * @param n The number of characters to duplicate
 * @return The duplicated string
 */
char	*ft_strndup(char const *s1, unsigned int n)
{
	char			*duplicate;
	unsigned int	index;

	index = 0;
	if (!s1 || n == 0)
		return (NULL);
	duplicate = malloc(sizeof(char) * (n + 1));
	if (duplicate == NULL)
		return (NULL);
	while (s1[index] && index < n)
	{
		duplicate[index] = s1[index];
		index++;
	}
	duplicate[index] = '\0';
	return (duplicate);
}
