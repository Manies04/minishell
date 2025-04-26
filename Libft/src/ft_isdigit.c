/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:51:31 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:02:36 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Variable is a digit
 * @param i Ascii representation
 * @return 1 if is a digit or 0 if not
*/
int	ft_isdigit(int i)
{
	if (i >= '0' && i <= '9')
		return (1);
	return (0);
}
/*#include <stdio.h>
int	main()
{
	char i = '1';
	printf("%d\n", ft_isdigit(i));
	return(0);
}*/