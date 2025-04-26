/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:15:13 by tiade-al          #+#    #+#             */
/*   Updated: 2025/04/18 23:42:41 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*@brief Concatenates two strings.
 * @param s1 str to be used
 * @param s2 str to append
 * @param free_line if 1 free if 0 don't free.
 * @return	the new concatenated string.
 */
char	*ft_strjoin(char *s1, char *s2, int free_line)
{
	char	*str;
	int		i;
	int		l;

	if (!s1 && free)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	str = (char *) malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (str == (void *)0)
		return ((void *)0);
	i = 0;
	l = -1;
	while (s1[++l])
		str[l] = s1[l];
	while (s2 && s2[i])
		str[l++] = s2[i++];
	if (free_line)
		free(s1);
	str[l] = '\0';
	return (str);
}
// int main(void)
// {
// 	char *d;
// 	d = ft_strjoin("fe", "liz");
// 	printf("Result is: %s\n", d);
// 	return (0);
// }