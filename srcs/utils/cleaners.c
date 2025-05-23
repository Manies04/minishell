/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:02:47 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/21 02:19:53 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **args)
{
	int	i;

	i = -1;
	if (!args)
		return ;
	while (args[++i])
	{
		free(args[i]);
		args[i] = NULL;
	}
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

void	exit_executor(t_exec *exec, int exit_status)
{
	if (exec)
	{
		close_pipe_ends(exec->fd);
		close_pipe_ends(exec->files);
		close_pipe_ends(exec->next_fd);
	}
	msh_inf()->quit = 0;
	if (exit_status != -1)
		msh_inf()->exit_status = exit_status;
}

char	**expand_variables(char **str, int *f)
{
	int		i;
	char	*sendable;
	char	*add;
	char	*expanded;

	*f = 0;
	i = need_expansion(str);
	while (i != -1)
	{
		if (i != 0 && ft_strcmp(str[i - 1], "\7\7") == 0)
			break ;
		sendable = get_var_name(str[i]);
		add = expand_var(sendable);
		expanded = add_expansion(&str[i], add, ft_strlen(sendable));
		str[i] = expanded;
		free(sendable);
		free(add);
		if (str_w_space(str[i]))
			str = split_by_spaces(str, i);
		(*f)++;
		i = need_expansion(str);
	}
	return (str);
}
