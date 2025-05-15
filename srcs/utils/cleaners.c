/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:02:47 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/15 17:15:26 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
		free(args[i++]);
	free(args);
}

void	free_double_array(char **array)
{
	int	i;
	
	i = 0;
	while (array && array[i])
		free(array[i++]);
	free(array);
}

void exit_executor(t_exec *exec, int exit_status)
{
	if (exec)
	{
		close_pipe_ends(exec->fd);
		close_pipe_ends(exec->files);
		close_pipe_ends(exec->next_fd);
	}
	msh_inf()->quit = 0;
	if (exit_status != -1)
		msh_inf()->exit_status = exit_status; // Set exit status
}
