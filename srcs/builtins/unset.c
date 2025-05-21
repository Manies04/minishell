/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:15:26 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/21 02:05:35 by tiade-al         ###   ########.fr       */
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
	int		i;
	size_t	token_len;
	size_t	env_key_len;

	i = 0;
	token_len = ft_strlen(token);
	while (env[i] != NULL)
	{
		env_key_len = 0;
		while (env[i][env_key_len] && env[i][env_key_len] != '=')
			env_key_len++;
		if (token_len == env_key_len && \
			ft_strncmp(env[i], token, token_len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

/**@brief This function removes a variable from the env and export arrays.
 * @param in_env != -1 if found in env.
 * @param in_export != -1 if found in export.
 * @return Void.
 */
static void	remove_from_envexport(int in_env, int in_export)
{
	int	i;

	if (in_env != -1)
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
	if (in_export != -1)
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

/**@brief This function removes variables from the env and export arrays.
 * @param token The list of tokens to remove.
 * @return Void.
 */
void	ft_unset(char **token)
{
	int	position;
	int	in_env;
	int	in_export;

	position = 0;
	while (token[++position])
	{
		if (ft_strchr(token[position], '=') != NULL)
			continue ;
		in_env = find_env_index(msh_inf()->env, token[position]);
		in_export = find_env_index(msh_inf()->export, token[position]);
		if (in_env == -1 && in_export == -1)
			continue ;
		if (in_env != -1 || in_export != -1)
			remove_from_envexport(in_env, in_export);
	}
}

/**@brief This function finds the first string needing expansion.
 * @param strs The array of strings to check
 * @return The index of the first string needing expansion, or -1 if none found
 */
int	need_expansion(char **strs)
{
	int	i;
	int	j;

	i = 0;
	while (strs[i])
	{
		handle_quoted_expansion(strs[i]);
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] == '\5')
			{
				j++;
				while (strs[i][j] && strs[i][j] != '\5')
					j++;
			}
			else if (strs[i][j] == '$' && strs[i][j + 1] && \
			strs[i][j + 1] != '\4' && strs[i][j + 1] != ' ')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

/**@brief This function checks if the string contains a space.
 * @param str The string to check
 * @return 1 if the string contains a space, 0 otherwise
 */
int	str_w_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 32)
			return (1);
		i++;
	}
	return (0);
}
