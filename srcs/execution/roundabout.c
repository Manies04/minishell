/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roundabout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 02:16:58 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/02 22:27:52 by tiade-al         ###   ########.fr       */
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

/* @brief This function checks if command exists in path by reading directory entries.
 * @param path The path to be checked.
 * @param command The command to be checked.
 * @return The path if found, NULL otherwise.
 */
static char	*check_directory(char *path, char *command)
{
	char			*valid_path;//holds the path to be checked
	struct dirent	*entity;// Holds information about a single directory entry like "ls" and  Allows checking each file in the directory to find command.
	DIR				*dir;// Enables iteration over directory contents to find a matching file.

	dir = opendir(path);// opens the directory specified by path
	if (!dir)
		return (NULL);
	entity = readdir(dir);// reads the first entry directory entry.
	valid_path = NULL;
	while (entity != NULL)// iterates through dir entries until it reaches the end (NULL)
	{
		if (!ft_strcmp(entity->d_name, command))// compares the entry's filename with command and if they are equal executes the block
		{
			valid_path = ft_strjoin(path, "/", 0);// if "/bin" returns "/bin/"
			valid_path = ft_strjoin(valid_path, command, 1);//"/bin/" + "ls" returns "/bin/ls"
			break ;
		}
		entity = readdir(dir);// reads the next directory entry
	}
	closedir(dir);// closes the directory stream
	return (valid_path);
}

/* @brief This function gets the path of the command by searching in the PATH variable.
 * @param command The command to be checked.
 * @return The valid path if found, NULL otherwise.
 */
static char	*get_path(char *command)
{
	char	*valid_path;//holds the valid path
	char	**directories;//holds the directories of PATH
	int		path_index;//holds the index of PATH in env
	int		i;

	valid_path = NULL;
	path_index = find_env_index(msh_inf()->env, "PATH");
	if (path_index == -1)//if not found, return NULL
		return (valid_path);
	directories = ft_split(ft_strchr(msh_inf()->env[path_index], '=') + 1, ':');//points to the first character after '=' and splits the string by ':'
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
	struct stat	info;//holds information about the file

	valid_path = NULL;
	if (command[0] == '/' || (command[0] == '.' && \
		(command[1] == '/' || command[1] == '.')))// checks if the command is an absolute (/) or relative path(./ or ../)
	{
		if (stat(command, &info) == 0)//checks if the file exists
			valid_path = ft_strdup(command);
	}
	else//if not absolute or relative path, for example "ls"
		valid_path = get_path(command);//////////path variable to search on
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

	if (!command)//if no command is given, exit
		ft_exit(NULL, 0);
	if (bultin_roundabout(command))//if builtin it gets executed and we then return
		return ;
	valid_path = check_valid_command(command[0], exec);//checks if the command is a valid path
	env = msh_inf()->env;
	if (execve(valid_path, command, env) == -1)//if error
	{
		perror(valid_path);
		free(valid_path);
		free_double_array(env);
		ft_exit(NULL, 126);
	}
}
