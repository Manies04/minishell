/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:58:35 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/02 13:50:56 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_process(void)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		exit(0);
	return (pid - 1);
}

int	is_redirection(char *str)
{
	if (!ft_strcmp(str, "\6") || \
			!ft_strcmp(str, "\6\6") || \
			!ft_strcmp(str, "\7") || \
			!ft_strcmp(str, "\7\7"))
			return (1);
	return (0);
}

int	is_whitespace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

void	redirect_error(char *file)//FIXME
{
	if (!ft_strcmp(file, "./\2/\2"))
		print_error("", "ambiguos redirect\n");
	else
		print_error(file, ": No such file or directory\n");
}

void	print_error(char *value, char *message)//FIXME
{
	write(STDERR_FILENO, value, ft_strlen(value));
	write(STDERR_FILENO, message, ft_strlen(message));
}
