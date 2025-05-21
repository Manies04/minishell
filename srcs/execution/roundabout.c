/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roundabout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 02:16:58 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/21 01:48:43 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*@brief This function checks if the command is a builtin or an external command
 *. If it is a builtin, it executes the command and returns 1, else 0.
 * @param commands The command to be checked.
 * @return 1 if it is a builtin, 0 otherwise.
 */
static int	bultin_roundabout(char **commands)
{
	int	is_builtin;

	is_builtin = 1;
	if (!ft_strcmp(commands[0], "exit"))
		ft_exit(commands, 0);
	else if (!ft_strcmp(commands[0], "pwd"))
		ft_pwd(1);
	else if (!ft_strcmp(commands[0], "echo"))
		ft_echo(commands, 1);
	else if (!ft_strcmp(commands[0], "env"))
		ft_env(commands, 1);
	else if (!ft_strcmp(commands[0], "export"))
		ft_export(commands, 1);
	else if (!ft_strcmp(commands[0], "unset"))
		ft_unset(commands);
	else if (!ft_strcmp(commands[0], "cd"))
		ft_cd(commands, 1);
	else
		is_builtin = 0;
	return (is_builtin);
}

/* @brief This function checks if command exists in path by reading directory 
	entries.
 * @param path The path to be checked.
 * @param command The command to be checked.
 * @return The path if found, NULL otherwise.
 */
static char	*check_directory(char *path, char *command)
{
	char			*valid_path;
	struct dirent	*entity;
	DIR				*dir;

	dir = opendir(path);
	if (!dir)
		return (NULL);
	entity = readdir(dir);
	valid_path = NULL;
	while (entity != NULL)
	{
		if (!ft_strcmp(entity->d_name, command))
		{
			valid_path = ft_strjoin(path, "/", 0);
			valid_path = ft_strjoin(valid_path, command, 1);
			break ;
		}
		entity = readdir(dir);
	}
	closedir(dir);
	return (valid_path);
}

/* @brief This function gets the path of the command by searching in the PATH
 variable.
 * @param command The command to be checked.
 * @return The valid path if found, NULL otherwise.
 */
static char	*get_path(char *command)
{
	char	*valid_path;
	char	**directories;
	int		path_index;
	int		i;

	valid_path = NULL;
	path_index = find_env_index(msh_inf()->env, "PATH");
	if (path_index == -1)
		return (valid_path);
	directories = ft_split(ft_strchr(msh_inf()->env[path_index], '=') + 1, ':');
	i = 0;
	while (directories[i])
	{
		valid_path = check_directory(directories[i], command);
		if (valid_path)
			break ;
		i++;
	}
	free_double_array(directories);
	return (valid_path);
}

/* @brief This function checks if the command is a valid path and returns it.
 * @param command The command to be checked.
 * @param exec The execution structure.
 * @return The valid path if found, NULL otherwise.
 */
char	*check_valid_command(char *command, t_exec *exec)
{
	char		*valid_path;
	struct stat	info;

	valid_path = NULL;
	if (!command)
		return (NULL);
	if (command[0] == '/' || (command[0] == '.' && \
		(command[1] == '/' || command[1] == '.')))
	{
		if (stat(command, &info) == 0)
			valid_path = ft_strdup(command);
	}
	else
		valid_path = get_path(command);
	if (!valid_path)
	{
		print_error(command, ": command not found\n");
		exit_executor(exec, 127);
	}
	return (valid_path);
}

/* @brief This function checks if the command is a builtin or an external 
 * command executing it.
 * @param command The command to be checked.
 * @return 1 if it is a builtin, 0 otherwise.
 */
void	executor_router(char **command, t_exec *exec)
{
	char	*valid_path;
	char	**env;

	if (!command || !command[0])
		exit(0);
	if (bultin_roundabout(command))
		return ;
	valid_path = check_valid_command(command[0], exec);
	if (!valid_path)
		exit(127);
	env = msh_inf()->env;
	if (execve(valid_path, command, env) == -1)
	{
		perror(valid_path);
		free(valid_path);
		exit(126);
	}
}
