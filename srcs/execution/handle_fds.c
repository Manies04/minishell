/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:33:39 by tiade-al          #+#    #+#             */
/*   Updated: 2025/04/21 22:45:21 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* @brief Closes the file descriptors if they are not set to -1 or -2.
 * @param fd The file descriptor array to close.
 * @return Void.
 */
void	close_pipe_ends(int *fd)
{
	if (fd)
	{
		if (fd && fd[0] != -1 && fd[0] != -2)
			close(fd[0]);
		if (fd && fd[1] != -1 && fd[1] != -2)
			close(fd[1]);
	}
}

/* @brief Closes a file descriptor if it is not set to -1.
 * @param fd The file descriptor to close.
 * @return Void.
 */
void	close_fd(int fd)
{
	if (fd != -1)
		close(fd);
}

/* @brief Initializes file descriptors to -1 to indicate they are not set yet.
 * @param fd1 Pointer to the first file descriptor array.
 * @param fd2 Pointer to the second file descriptor array.
 * @return Void.
 */
void	init_fds(int (*fd1)[2], int (*fd2)[2])
{
	if (fd1)
	{
		(*fd1)[0] = -1;
		(*fd1)[1] = -1;
	}
	if (fd2)
	{
		(*fd2)[0] = -1;
		(*fd2)[1] = -1;
	}
}
