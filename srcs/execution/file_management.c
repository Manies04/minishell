/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:22:55 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/02 23:27:16 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*@brief This function gets the input from the heredoc.
 * @param current A pointer to the current command.
 * @param i The index of the heredoc.
 * @return The heredoc input.
 */
static char	*get_heredoc_input(t_commands *current, int i)
{
	char	*str;//stores the accumulated heredoc input
	char	*input;//strores the current line of input

	str = NULL;
	while (1)
	{
		input = readline("> ");//prompts the user for input
		if (msh_inf()->quit)
		{
			if (str)
				free(str);
			str = NULL;
			break ;
		}
		if (input == NULL)// if EOF is reached (ctrl-d)
			return (printf("(wanted '%s').\n", \
				current->heredocs[i]), str);
		if (!ft_strcmp(input, current->heredocs[i]))//if the input matches the heredoc delimiter
			return (free(input), str);
		str = ft_strjoin(str, input, 1);
		str = ft_strjoin(str, "\n", 1);
		free(input);
	}
	return (str);
}

/*@brief This function creates a temporary file with the input from heredoc.
 * @param current A pointer to the current command.
 * @param exec A pointer to the execution structure.
 * @param i The index of the heredoc.
 * @return Void.
 */
static void	create_temp_file(t_commands *current, t_exec *exec, int i)
{
	char	*str;// stores the heredoc input
	int		fd;//stores the fd for the temporary file

	signal(SIGINT, sig_for_heredoc);// sets the signal handler for ctrl+c
	fd = open(".temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);//opens or creates the temp file for writing. The "." before tempmakes it a hidden file.
	str = get_heredoc_input(current, i);//gets the heredoc input from the user
	if (msh_inf()->quit)//checks if ctrl+c was pressed
	{
		close(fd);
		exit_executor(exec, 1);
	}
	expand_heredoc(&str);//FIXME think it's done(bellow func works) expands the environment variables in the heredoc input
	write(fd, str, ft_strlen(str));//writes the heredoc input to the temp file
	close(fd);
	free(str);
	exit_executor(exec, 0);// exits the child process with success.
}

/*@brief This function processes the heredoc files for the current command.
 * @param current A pointer to the current command.
 * @param exec A pointer to the execution structure.
 * @return The file descriptor for the temporary file.
*/
static int	heredoc_process(t_commands *current, t_exec *exec)
{
	int	tmp;//stores the fd of the temp file
	int	i;//iterate over the array of heredoc files
	int	pid;//process id of the child process

	i = 0;
	tmp = -1;//hasn't been opened yet
	while (current->heredocs && current->heredocs[i])//processes each hearddoc in heardoc[i]
	{
		pid = fork();//creates a child process
		if (pid == 0)//if we are in the child process
			create_temp_file(current, exec, i);//creates a temp file for the heredoc input
		waitpid(pid, &msh_inf()->quit, 0);//wait for the child process to finish
		if (msh_inf()->quit)
		{
			msh_inf()->exit_status = 130 * 256;//130 is the exit status for ctrl+c and 256 is how it's stored in the waitpid function
			break ;
		}
		i++;
	}
	if (!msh_inf()->quit)//if not interrupted
		tmp = open(".temp.txt", O_RDONLY, 0777);//open the temp file in read only mode
	return (tmp);
}

/**@brief This function handles the input redirection (<, <<) for the current 
 * command.
 * @param current A pointer to the current command.
 * @param exec A pointer to the execution structure.
 * @return The file descriptor for the input redirection.
 */
int	input_redirect(t_commands *current, t_exec *exec)
{
	int	i;//iterate over the array of input redirection files
	int	input;//fd for the last successful opened input file.
	int	heredoc;//fd for the last successful opened heredoc file.

	i = -1;
	input = -1;//indicate that no input file has been opened yet.
	if (!current->input)//if there is no input redirection(<, <<)
		return (-1);
	heredoc = heredoc_process(current, exec);//process heredoc files if any
	if (msh_inf()->quit)//if ctrl+c was pressed, exit the program
		return (-1);
	while (current->infiles && current->infiles[++i] && input != -2)//ensures there are input files and checks if the input file at position[i] is valid, and if there is no problem opening it.
	{
		close_fd(input);//ensures only one file is open at a time.
		input = open(current->infiles[i], O_RDONLY, 0777);//open in read only mode, is 0777 really neded?
		if (input == -1)//open failed
			input = -2;//flag to indicate that the file was not opened successfully and end the loop.
	}
	if (input == -2)
		redirect_error(current->infiles[i - 1]);// passes the last working file to the error function. ///////////////////////////////////////why??
	if (!ft_strcmp(current->input, "\7\7") && input != -2)// if the less than is a heredoc, and the input file was opened successfully.
		return (close_fd(input), heredoc);//close the input file and return the heredoc file descriptor.
	return (close_fd(heredoc), input);//close the heredoc file and return the input file descriptor.
}

/**@brief This function handles the output redirection (>, >>) for the commands.
 * @param current A pointer to the current command.
 * @param exec A pointer to the execution structure.
 * @return The fd for the last successfully opened output file.
 */
int	output_redirect(t_commands *current, t_exec *exec)
{
	int		i;//iterate over the array of output & outfiles
	int		fd;//fd for the last successfully opened output file.
	int		flag;//flag to indicate if the file should be truncated or appended.

	if (!current->output || exec->files[0] == -2)//checks if there's any output redirection and if there was an error opening the input file.
		return (-1);
	i = 0;
	fd = -1;//hasnt been opened
	while (current->outfiles[i] && fd != -2)//there's a filename and file was opened successfully
	{
		close_fd(fd);//ensures only the final output file is open.
		flag = O_APPEND;//default to append mode(>>)
		if (!ft_strcmp(current->output[i], "\6"))//truncate mode(>)overwrites the file
			flag = O_TRUNC;
		fd = open(current->outfiles[i], O_WRONLY | O_CREAT | flag, 0777);
		if (fd == -1)
			fd = -2;
		i++;
	}
	if (fd == -2)
		redirect_error(current->outfiles[i - 1]);// last file attempted
	return (fd);
}
