/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:07:35 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:04:57 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Allocates a new string suplicated by 'src'
 * @param *src Pointer to a string that will be duplicated
 * @return A new string duplicated by 'src'
*/
char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(ft_strlen(src) * sizeof(char) + 1);
	if (dest)
	{
		while (src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
	}
	else
		return (NULL);
	dest[i] = '\0';
	return (dest);
}
/*int main()
{
	const char *original = "Hello, world!";
	char *copied;

	copied = ft_strdup(original);

	if (copied != NULL)
	{
		printf("String original: %s\n", original);
		printf("String duplicada: %s\n", copied);
		free(copied);
	}
	else
	{
		printf("Erro: falha ao duplicar a string.\n");
	}
	return (0);
}*/