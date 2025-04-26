/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:39:26 by tiade-al          #+#    #+#             */
/*   Updated: 2025/04/25 00:21:44 by tiade-al         ###   ########.fr       */
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
	pwd = getcwd(NULL, 0);//get current working driver
	if (!pwd)//if not found get the last known wd
		pwd = ft_strdup(msh_inf() ->pwd);
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

/**@brief This function updates the current working directory in the shell info structure.
 * @return Void.
 */
void	pwd_updater(void)//is it really needed?
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);//get current working driver
	if (pwd)
	{
		free(msh_inf() -> pwd);//clear previous wd
		msh_inf() -> pwd = pwd;//updates that position
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
		return(false);
	i = 2;//skips the first "-n"
	while (str[i] == 'n')//checks for multiple n's
		i++;
	return(str[i] == '\0');//checks if next char after all n's
}

/**@brief This function is used to print the arguments passed to it.
 * @param cmd The list of commands.
 * @param fd The file descriptor to write to.
 * @return Void.
 */
void	ft_echo(char **cmd, int fd)
{
	int		i;
	bool	nflag;

	i = 1;//skips the "echo"
	nflag = false;
	if (cmd[1] && echonflag(cmd[1]))//if the flag and the cmd are present flag it and move to the next cmd after "-n"
	{
		nflag = true;
		i++;
	}
	while (cmd[i] && echonflag(cmd[i]))//skip multiple "-n"
		i++;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd);//write the string to fd
		if (cmd[i + 1] != NULL)//if there is another string incoming 
			write(fd, " ", 1);
		i++;
	}
	if (!nflag)//if no flag, new line
		write(fd, "\n", 1);
}

/**@brief This function is used to retrieve the VALUE of an env variable (whats after '=')
 * @param str The variable to get VALUE from.
 * @return The value of the variable.
 */
static char	*value_helper(const char *str)
{
	int		i;
	char	*value;

	printf("...getting value for cd: '%s'\n\n", str);
	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
		return (ft_strdup(""));
	i++;  // Skip the '='
	value = ft_strdup(&str[i]);  // Duplicate the substring directly
	if (!value)
		return (NULL);
	printf("VALUE: '%s'\n\n", value);
	return (value);
}

/**@brief This function checks if the wanted variable is in the env list and returns its value.
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
		if (ft_strncmp(wanted, env[i], ft_strlen(wanted)) == 0 && env[i][ft_strlen(wanted)] == '=')
		{
			printf("found\n");
			return (value_helper(env[i]));
		}
	}
	return (ft_strdup(""));
}

/**@brief This function changes the current working directory to the one specified in cmd[1].
 * @param cmd The list of commands.
 * @param fd The file descriptor to write to.
 * @return Void.
 */
void	ft_cd(char **cmd, int fd)
{
	char	env_var[4128]; // "PWD=" + path + safety(28bytes). PATH_MAX
	char	wd[4096]; //PATH_MAX

	if (!cmd[1] || (!ft_strncmp(cmd[1], "~/", ft_strlen("~/"))
			&& ft_strlen(cmd[1]) == ft_strlen("~/"))
		|| (cmd[1][0] == '~' && !cmd[1][1])) // to go HOME;
		cmd[1] = get_var_value("HOME");
	if (chdir(cmd[1]) == -1)//if failiure to change directory
	{
		write(2, "minishell: cd: ", 15);//Starts an error message if chdir fails
		perror(cmd[1]);
		msh_inf()->exit_status = 1;
		return ;
	}
	if (getcwd(wd, sizeof(wd)) == NULL)//gets the cwd and checks if it fails
	{
		perror("minishell: pwd: ");
		msh_inf()->exit_status = 1;
		return ;
	}
	ft_strlcpy(env_var, "PWD=", sizeof(env_var));//Copies "PWD=" into env_var.
	ft_strlcat(env_var, wd, sizeof(env_var));
	//update_pwd (is it really needed?)
	ft_export((char *[]){"export", env_var, NULL}, fd);//updates PWD on export/env.
	msh_inf()->exit_status = 0;
}


/*
//////////
/  DONE  /
//////////

◦ pwd with no options
◦ echo with option -n (   -n   Do not output a trailing newline.)
◦ exit with no options 
◦ env with no options or arguments
◦ export with no options
◦ unset with no options
◦ cd with only a relative or absolute path
*/