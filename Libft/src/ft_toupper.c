/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:55:53 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:05:50 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Character has to be uppercase
 * @param content If character is lowercase, puts it in uppercase
 * @return The character in Uppercase
*/
int	ft_toupper(int i)
{
	if (i >= 'a' && i <= 'z')
		i -= 32;
	return (i);
}
/*
int	main()
{
	char i = 'a';
	printf("%c\n", ft_toupper(i));
	return(0);
}*/