/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:02:47 by tiade-al          #+#    #+#             */
/*   Updated: 2025/03/12 10:56:48 by tiade-al         ###   ########.fr       */
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
	t_msh	*msh;
	int c = 0;

	msh = msh_inf();
	free(msh->pwd);
	////////////env
	while (msh->env[c])
		free(msh->env[c++]);
	free(msh->env);
	///////////
	
}

void	clean_all(void)
{
	free_structs();
}