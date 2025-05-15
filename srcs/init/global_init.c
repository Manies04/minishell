/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:49:34 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/15 17:33:35 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cpy_env(char **env)
{//copies env and a cpy to use in export
	int	c;

	c = 0;
	while (env[c])
		c++;
	if (msh_inf()->env)  // Free old env if it exists
		free_array(msh_inf()->env);
	if (msh_inf()->export)  // Free old export if it exists
		free_array(msh_inf()->export);
	msh_inf()->env = ft_calloc(sizeof(char *), c + 1);
	msh_inf()->export = ft_calloc(sizeof(char *), c + 1);
	c = -1;
	while (env[++c])
	{
		msh_inf()->env[c] = ft_strdup(env[c]);//leaks
		msh_inf()->export[c] = ft_strdup(env[c]);//leaks
	}
}

t_msh	*msh_inf(void)
{
	static	t_msh	msh;//static initializes everything insite the struct to 0 once
	
	return (&msh);
}

void	read_input(char *input)
{
	char	*new;

	add_history(input);//adds the input to the history
	new = lexer(input);
	free(input);
	if (!new)
		return ;
	parser(new);
	free(new);
	executor(&msh_inf()->commands);
	free_commands(msh_inf()->commands);
	msh_inf()->commands = NULL;
}
