/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_II.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:04:22 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/21 01:56:01 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief This function adds a new environment variable to the environment 
 * array.
 * @param arg The new environment variable to add.
 * @param env_ptr Pointer to the environment array.
 * @return Void.
 */
void	add_new_env_var(char *arg, char ***env_ptr)
{
	char	**env;
	char	**new_env;
	int		i;

	env = *env_ptr;
	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = ft_strdup(arg);
	new_env[i + 1] = NULL;
	free(env);
	*env_ptr = new_env;
}

/**@brief This function handles invalid identifiers for export.
 * @param arg The invalid identifier.
 * @param fd The file descriptor to write to.
 * @return 1 if the identifier is invalid.
 */
int	handle_invalid_identifier(char *arg, int fd)
{
	printf("arg: %s\n", arg);
	write(fd, "minishell: export: `", 20);
	write(fd, arg, ft_strlen(arg));
	write(fd, "': not a valid identifier\n", 26);
	return (1);
}

/**@brief This function creates a duplicate of an environment variable array.
 * @param env The stored exported variables.
 * @param env_copy Used to keep the copy of env.
 * @param count The end of the list.
 * @return Void.
 */
void	copy_env_array(char **env, char **env_copy, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		env_copy[i] = ft_strdup(env[i]);
		if (!env_copy[i])
		{
			free_array(env_copy);
			return ;
		}
		i++;
	}
}

/**@brief This function prints to the terminal the exported variables as they
 *  are suppose to be displayed.
 * @param env_copy Used to keep the copy of env.
 * @param fd The fd to write to.
 * @return Void.
 */
void	print_sorted_env(char **env_copy, int fd)
{
	int		i;
	char	*equal_sign;

	i = 0;
	while (env_copy[i])
	{
		write(fd, "declare -x ", 11);
		equal_sign = ft_strchr(env_copy[i], '=');
		if (!equal_sign)
			write(fd, env_copy[i], ft_strlen(env_copy[i]));
		else
		{
			write(fd, env_copy[i], equal_sign - env_copy[i]);
			write(fd, "=\"", 2);
			write(fd, equal_sign + 1, ft_strlen(equal_sign + 1));
			write(fd, "\"", 1);
		}
		write(fd, "\n", 1);
		i++;
	}
}

/**@brief This function checks if a string starts with a letter or underscore 
 * and if encounters '=' it stops.
 * @param str The string to check.
 * @return 1 if valid, 0 otherwise.
 */
int	is_valid_identifier(char *str)
{
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}
