/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:56:49 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:05:47 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Character has to be lowercase
 * @param content If character is uppercase, puts it in lowercase
 * @return The character in lowercase
*/
int	ft_tolower(int i)
{
	if (i >= 'A' && i <= 'Z')
		i += 32;
	return (i);
}
/*
int	main()
{
	char i = 'A';
	printf("%c\n", ft_tolower(i));
	return(0);
}*/