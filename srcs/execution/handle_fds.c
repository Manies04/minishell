/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:33:39 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/21 01:49:09 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_pipe_ends(int *fd)
{
	if (fd)
	{
		if (fd[0] >= 0)
			close(fd[0]);
		if (fd[1] >= 0)
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

/**@brief This function removes empty strings("") from an array of strings.
 * @param strs The array of strings to edit
 * @return The edited array, without empty strings
 */
char	**rm_empty_str(char **strs)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = ft_cp_double_str(strs);
	free(strs);
	strs = (char **)malloc(sizeof(char *) * (count_strs(temp) + 1));
	if (!strs)
		return (NULL);
	while (temp[i])
	{
		if (ft_strcmp(temp[i], "") != 0)
			strs[j++] = temp[i++];
		else
			free(temp[i++]);
	}
	strs[j] = NULL;
	free(temp);
	return (strs);
}

/**@brief This function removes all quotes and replaces \1 with $ for every str 
 * in the array.
 * @param strs The array of strings to edit
 * @return The edited array of strings
 */
char	**rm_quotes(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		edit_str(&strs[i]);
		i++;
	}
	return (strs);
}
