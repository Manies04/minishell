/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:52:59 by jhenriq2          #+#    #+#             */
/*   Updated: 2025/04/23 15:02:39 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**@brief Variable is printable
 * @param i Ascii representation
 * @return 1 if is printable or 0 if not
*/
int	ft_isprint(int i)
{
	if (i >= 32 && i <= 126)
		return (1);
	return (0);
}
/*#include <stdio.h>
int	main()
{
	char i = 10;
	printf("%d\n", ft_isprint(i));
	return(0);
}*/