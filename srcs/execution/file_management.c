/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:22:55 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/21 00:33:48 by tiade-al         ###   ########.fr       */
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
	char	*str;
	char	*input;

	str = NULL;
	while (1)
	{
		input = readline("> ");
		if (msh_inf()->quit)
		{
			if (str)
				free(str);
			str = NULL;
			break ;
		}
		if (input == NULL)
			return (printf("(wanted '%s').\n", \
				current->heredocs[i]), str);
		if (!ft_strcmp(input, current->heredocs[i]))
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
	char	*str;
	int		fd;

	signal(SIGINT, sig_for_heredoc);
	fd = open(".temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	str = get_heredoc_input(current, i);
	if (msh_inf()->quit)
	{
		close(fd);
		exit_executor(exec, 1);
	}
	expand_heredoc(&str);
	write(fd, str, ft_strlen(str));
	close(fd);
	free(str);
	exit_executor(exec, 0);
}

/*@brief This function processes the heredoc files for the current command.
 * @param current A pointer to the current command.
 * @param exec A pointer to the execution structure.
 * @return The file descriptor for the temporary file.
*/
static int	heredoc_process(t_commands *current, t_exec *exec)
{
	int	tmp;
	int	i;
	int	pid;

	i = 0;
	tmp = -1;
	while (current->heredocs && current->heredocs[i])
	{
		pid = fork();
		if (pid == 0)
			create_temp_file(current, exec, i);
		waitpid(pid, &msh_inf()->quit, 0);
		if (msh_inf()->quit)
		{
			msh_inf()->exit_status = 130 * 256;
			break ;
		}
		i++;
	}
	if (!msh_inf()->quit)
		tmp = open(".temp.txt", O_RDONLY, 0777);
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
	int	i;
	int	input;
	int	heredoc;

	i = -1;
	input = -1;
	if (!current->input)
		return (-1);
	heredoc = heredoc_process(current, exec);
	if (msh_inf()->quit)
		return (-1);
	while (current->infiles && current->infiles[++i] && input != -2)
	{
		close_fd(input);
		input = open(current->infiles[i], O_RDONLY, 0777);
		if (input == -1)
			input = -2;
	}
	if (input == -2)
		redirect_error(current->infiles[i - 1]);
	if (!ft_strcmp(current->input, "\7\7") && input != -2)
		return (close_fd(input), heredoc);
	return (close_fd(heredoc), input);
}

/**@brief This function handles the output redirection (>, >>) for the commands.
 * @param current A pointer to the current command.
 * @param exec A pointer to the execution structure.
 * @return The fd for the last successfully opened output file.
 */
int	output_redirect(t_commands *current, t_exec *exec)
{
	int		i;
	int		fd;
	int		flag;

	if (!current->output || exec->files[0] == -2)
		return (-1);
	i = 0;
	fd = -1;
	while (current->outfiles[i] && fd != -2)
	{
		close_fd(fd);
		flag = O_APPEND;
		if (!ft_strcmp(current->output[i], "\6"))
			flag = O_TRUNC;
		fd = open(current->outfiles[i], O_WRONLY | O_CREAT | flag, 0777);
		if (fd == -1)
			fd = -2;
		i++;
	}
	if (fd == -2)
		redirect_error(current->outfiles[i - 1]);
	return (fd);
}
