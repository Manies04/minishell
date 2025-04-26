/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:22:14 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:05:03 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Concatenate two strings into a new one
 * @param content Copies the content of s1 and s2 into the new str
 * @param s1 Source 1
 * @param s2 Source 2
 * @return The new string
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
/*int	main()
{
	const char	*s1 = "Hello, ";
	const char	*s2 = "world!";
	char	*result = ft_strjoin(s1, s2);

	printf("Strings concatenadas: %s\n", result);
	free(result);
	return 0;
}*/
