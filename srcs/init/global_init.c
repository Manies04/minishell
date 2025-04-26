/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:49:34 by tiade-al          #+#    #+#             */
/*   Updated: 2025/03/20 17:41:44 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* static void	cpy_env(char **env) ////previous
{
	int	c;

	c = 0;
	while (env[c])//get size
		c++;
	msh_inf()->env = ft_calloc (sizeof(char *), c + 1);//allocate memory LEAKSSSS!!!!!!!
	c = -1;
	while (env[++c])
		msh_inf()->env[c] = ft_strdup(env[c]);//copy everythig stored in env to the struct LEAKSSSS!!!!!!!!!!!
} */

static void	cpy_env(char **env)//copies env end a cpy to use in export
{
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
		msh_inf()->env[c] = ft_strdup(env[c]);
		msh_inf()->export[c] = ft_strdup(env[c]);
	}
}

//initiation of variables
void	minishell_init(char **env)
{
	t_msh	*msh;//main struct
	
	msh = msh_inf();
	msh->pwd = getcwd(NULL, 0);
	cpy_env(env);
}

t_msh	*msh_inf(void)
{
	static	t_msh	msh;//static initializes everything insite the struct to 0 once
	
	return (&msh);
}