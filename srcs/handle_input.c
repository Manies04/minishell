/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:35:27 by joaoleote         #+#    #+#             */
/*   Updated: 2025/04/26 11:49:19 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	read_input(char *input)
{
	char	*new;

	add_history(input);
	new = lexer(input);
	if (!new)
		return ;
	parser(new);
	free(new);
	executor(&msh_inf()->commands);
	free_commands(msh_inf()->commands);
	msh_inf()->commands = NULL;
}
