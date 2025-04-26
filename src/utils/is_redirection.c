/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:25:00 by joaoleote         #+#    #+#             */
/*   Updated: 2025/04/25 17:38:10 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_redirection(char *str)
{
	if (!ft_strcmp(str, GREAT_MARKER) || \
			!ft_strcmp(str, "\x15\x15") || \
			!ft_strcmp(str, LESS_MARKER) || \
			!ft_strcmp(str, "\x14\x14"))
			return (1);
	return (0);
}
