/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:15:26 by tiade-al          #+#    #+#             */
/*   Updated: 2025/04/20 16:39:26 by tiade-al         ###   ########.fr       */
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

void	ft_unset(char **token)
{
	char **env = msh_inf()->env;		// Access env from structure (only entries with '=')
	char **export = msh_inf()->export;	// Access export from structure (all entries)
	int position = 0;
	int in_env, in_export;
	int i, ii;

	while (token[++position]) // For every token
	{
		printf("token: %s\n", token[position]);

		// Skip tokens with '=' (e.g., "batta1=", "batata2=yes")
		if (ft_strchr(token[position], '=') != NULL)
			continue;

		in_env = find_env_index(env, token[position]);    // Check env
		in_export = find_env_index(export, token[position]); // Check export

		if (in_env == -1 && in_export == -1)
			continue; // Token not found, skip to next token

		// Remove from env if found (e.g., "batta1" matches "batta1=")
		if (in_env != -1)
		{
			free(env[in_env]);
			i = in_env;
			while (env[i + 1] != NULL)
			{
				env[i] = env[i + 1];
				i++;
			}
			env[i] = NULL;
		}

		// Remove from export if found (e.g., "batta1" matches "batta1=")
		if (in_export != -1)
		{
			free(export[in_export]);
			ii = in_export;
			while (export[ii + 1] != NULL)
			{
				export[ii] = export[ii + 1];
				ii++;
			}
			export[ii] = NULL;
		}
	}
}
