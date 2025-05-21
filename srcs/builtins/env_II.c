/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_II.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 01:09:15 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/21 02:02:48 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief This function uses Bubble sort implementation for sorting the cpy of
 *  env array
 * @param env The copy of env.
 * @param size The end of the list.
 * @return Void.
 */
void	sort_env(char **env, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

/**@brief This function finds the index of a key in the env array.
 * @param key The key to find.
 * @param env The env array.
 * @return The index of the key in the env array, or -1 if not found.
 */
int	env_find(char *key, char **env)
{
	int	i;
	int	len;

	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && (env[i][len] == '=' \
			|| env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

/**@brief Initializes environment variable components by parsing the input 
 * argument.
 * @param arg The input string containing the variable (e.g., "KEY=value" 
 * or "KEY").
 * @param key Pointer to store the extracted key (portion before '=').
 * @param new_var Pointer to store the full variable string (key or key=
 * value).
 * @param equal_sign Pointer to store the address of the '=' character, 
 * if present.
 * @return 0 on success, -1 on memory allocation failure.
 */
static int	init_env_var(char *arg, char **key, char **new_var, char **eql_sign)
{
	*eql_sign = ft_strchr(arg, '=');
	if (*eql_sign)
	{
		*key = ft_substr(arg, 0, *eql_sign - arg);
		if (!*key)
			return (-1);
		*new_var = ft_strdup(arg);
	}
	else
	{
		*key = ft_strdup(arg);
		if (!*key)
			return (-1);
		*new_var = ft_strdup(arg);
	}
	if (!*new_var)
	{
		free(*key);
		return (-1);
	}
	return (0);
}

/**@brief Updates the environment array with a new variable if it contains an 
 * '='.
 * @param key The variable key to update or add.
 * @param new_var The full variable string (key=value).
 * @param equal_sign Pointer to the '=' character in new_var, or NULL if absent.
 * @return Void.
 */
static void	update_env(char *key, char *new_var, char *equal_sign)
{
	int	index;

	if (!equal_sign)
		return ;
	index = env_find(key, msh_inf()->env);
	if (index >= 0)
	{
		free(msh_inf()->env[index]);
		msh_inf()->env[index] = ft_strdup(new_var);
	}
	else
		add_new_env_var(new_var, &msh_inf()->env);
}

/**@brief Sets an environment variable by updating both export and env arrays
 *  if valid.
 * @param arg The input string containing the variable (e.g., "KEY=value" or
 *  "KEY").
 * @param fd The file descriptor to write error messages to.
 * @return 0 on success, 1 if the identifier is invalid or an error occurs.
 */
int	set_env_var(char *arg, int fd)
{
	char	*equal_sign;
	char	*key;
	char	*new_var;

	if (init_env_var(arg, &key, &new_var, &equal_sign) < 0)
		return (1);
	if (!is_valid_identifier(key))
	{
		free(key);
		free(new_var);
		return (handle_invalid_identifier(arg, fd));
	}
	update_export(key, new_var, equal_sign);
	update_env(key, new_var, equal_sign);
	free(key);
	free(new_var);
	return (0);
}
