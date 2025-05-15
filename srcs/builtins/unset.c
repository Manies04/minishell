/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:15:26 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/14 13:32:25 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief This function finds the index of a variable in the env or export list.
 * @param env The environment array to search.
 * @param token The exact variable name to find (no '=' allowed in token).
 * @return Index if found, -1 otherwise.
 */
int	find_env_index(char **env, const char *token)
{
	int i = 0;
	size_t token_len = ft_strlen(token); // Length of the token (e.g., "batta1")

	while (env[i] != NULL)
	{
		// For both env and export: match token against the variable name (up to '=' if present)
		size_t env_key_len = 0;
		while (env[i][env_key_len] && env[i][env_key_len] != '=')
			env_key_len++;
		if (token_len == env_key_len && ft_strncmp(env[i], token, token_len) == 0)
			return (i); // e.g., "batta1" matches "batta1=" or "batata2" matches "batata2=yes"
		i++;
	}
	return (-1);
}
static void	remove_from_envexport(int in_env, int in_export)
{
	int	i;
	
	if (in_env != -1)	// Remove from env if found (e.g., "batta1" matches "batta1=")
	{
		free(msh_inf()->env[in_env]);
		i = in_env;
		while (msh_inf()->env[i + 1] != NULL)
		{
			msh_inf()->env[i] = msh_inf()->env[i + 1];
			i++;
		}
		msh_inf()->env[i] = NULL;
	}
	if (in_export != -1)	// Remove from export if found (e.g., "batta1" matches "batta1=")
	{
		free(msh_inf()->export[in_export]);
		i = in_export;
		while (msh_inf()->export[i + 1] != NULL)
		{
			msh_inf()->export[i] = msh_inf()->export[i + 1];
			i++;
		}
		msh_inf()->export[i] = NULL;
	}
}
void	ft_unset(char **token)
{
	int	position;
	int	in_env;
	int	in_export;

	position = 0;
	while (token[++position]) // For every token
	{
		// Skip tokens with '=' (e.g., "batta1=", "batata2=yes")
		if (ft_strchr(token[position], '=') != NULL)
			continue;

		in_env = find_env_index(msh_inf()->env, token[position]);    // Check env
		in_export = find_env_index(msh_inf()->export, token[position]); // Check export

		if (in_env == -1 && in_export == -1)
			continue; // Token not found, skip to next token
		if (in_env != -1 || in_export != -1)
			remove_from_envexport(in_env, in_export); // Remove from env and export
	}
}
