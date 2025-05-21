/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:49:34 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/21 01:46:58 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cpy_env(char **env)
{
	int	c;

	c = 0;
	while (env[c])
		c++;
	if (msh_inf()->env)
		free_array(msh_inf()->env);
	if (msh_inf()->export)
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

t_msh	*msh_inf(void)
{
	static t_msh	msh;

	return (&msh);
}

void	read_input(char *input)
{
	char	*new;

	add_history(input);
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

void	init_vars(int *a, int *b, int *c)
{
	if (a)
		*a = 0;
	if (b)
		*b = 0;
	if (c)
		*c = 0;
}

/**@brief Appends remaining text after last variable to result.
 * @param result Current result string
 * @param temp Input string
 * @return Updated result string
 */
char	*append_remaining(char *result, char *temp)
{
	char	*remaining;
	char	*new_result;

	remaining = ft_strdup(temp);
	new_result = ft_strjoin(result, remaining, 0);
	free(result);
	free(remaining);
	return (new_result);
}
