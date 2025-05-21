/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:39:26 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/21 02:07:10 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief This function is used to print the current working directory.
 * @param fd The file descriptor to write to.
 * @return Void.
 */
void	ft_pwd(int fd)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		write(fd, pwd, ft_strlen(pwd));
		write(fd, "\n", 1);
		free(pwd);
	}
	else
	{
		perror("!!!ERROR!!! PWD");
		msh_inf()->exit_status = 1;
	}
}

/**@brief This function checks if the string is '-n' flag for echo.
 * @param str The string to check for '-n'.
 * @return True if the string is '-n', false otherwise.
 */
bool	echonflag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (false);
	i = 2;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

/**@brief This function is used to retrieve the VALUE of an env variable (whats 
 * after '=')
 * @param str The variable to get VALUE from.
 * @return The value of the variable.
 */
static char	*value_helper(const char *str)
{
	int		i;
	char	*value;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
		return (ft_strdup(""));
	i++;
	value = ft_strdup(&str[i]);
	if (!value)
		return (NULL);
	return (value);
}

/**@brief This function checks if the wanted variable is in the env list and 
 * returns its value.
 * @param wanted The variable to search for.
 * @return The value of the variable if found, NULL otherwise.
 */
static char	*get_var_value(char *wanted)
{
	char	**env;
	int		i;

	env = msh_inf()->env;
	i = -1;
	if (!env || !wanted)
		return (NULL);
	if (!*wanted)
		return (ft_strdup(""));
	while (env[++i])
	{
		if (ft_strncmp(wanted, env[i], ft_strlen(wanted)) == 0 && \
			env[i][ft_strlen(wanted)] == '=')
			return (value_helper(env[i]));
	}
	return (ft_strdup(""));
}

/**@brief This function changes the current working directory to the one 
 * specified in cmd[1].
 * @param cmd The list of commands.
 * @param fd The file descriptor to write to.
 * @return Void.
 */
void	ft_cd(char **cmd, int fd)
{
	char	env_var[4128];
	char	wd[4096];

	if (!cmd[1] || (!ft_strncmp(cmd[1], "~/", ft_strlen("~/"))
			&& ft_strlen(cmd[1]) == ft_strlen("~/"))
		|| (cmd[1][0] == '~' && !cmd[1][1]))
		cmd[1] = get_var_value("HOME");
	if (chdir(cmd[1]) == -1)
	{
		write(2, "minishell: cd: ", 15);
		perror(cmd[1]);
		msh_inf()->exit_status = 1;
		return ;
	}
	if (getcwd(wd, sizeof(wd)) == NULL)
	{
		perror("minishell: pwd: ");
		msh_inf()->exit_status = 1;
		return ;
	}
	ft_strlcpy(env_var, "PWD=", sizeof(env_var));
	ft_strlcat(env_var, wd, sizeof(env_var));
	ft_export((char *[]){"export", env_var, NULL}, fd);
	msh_inf()->exit_status = 0;
}
