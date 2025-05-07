/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:02:47 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/02 22:24:24 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **args)
{
	int i = 0;

	if (!args)
		return ;
	while (args[i])
		free(args[i++]);
	free(args);
}

void	free_structs(void)
{
	int c;

	c = -1;
	free(msh_inf()->pwd);
	////////////env/export
	while (msh_inf()->env[++c])
	{
		free(msh_inf()->env[c]);
		free(msh_inf()->export[c]);
	}
	free(msh_inf()->env);
	free(msh_inf()->export);
}

void	clean_all(void)//FIXME not very well used only 1 func
{
	free_structs();
}

void	free_double_array(char **array)
{
	int	i;
	
	i = 0;
	while (array && array[i])
		free(array[i++]);
	free(array);
}

void	exit_executor(t_exec *exec, int exit_status)
{
	//free(exec->pids);//FIXME double free cause?
	msh_inf()->quit = 0;
	close_pipe_ends(exec->fd);
	close_pipe_ends(exec->files);
	close_pipe_ends(exec->next_fd);
	if (exit_status != -1)
		ft_exit(NULL, exit_status);
	return ;
}