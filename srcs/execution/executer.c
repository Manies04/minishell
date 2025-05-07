/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:54:50 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/04 15:18:32 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/**@brief This function
 * @param fd A pointer to the file descriptors to be initialized.
 * @param current A pointer to the current command.
 * @param exec A pointer to the execution structure.
 * @return Void.
 */
//2nd
static int	do_multable_builtin(t_commands *current, t_exec *exec)
{
	int i;

	i = 0;
	if (!current->command)
		return (0);//export batata stays only in 1 command so the next command is NULL, for it to have 2 commands it would have to have pipes (|), redirections (>).
	if (!current->next && \
		(!ft_strcmp(current->command[0], "exit") || \
		!ft_strcmp(current->command[0], "export") || \
		!ft_strcmp(current->command[0], "unset") || \
		!ft_strcmp(current->command[0], "cd")))
	{
		exec->files[0] = input_redirect(current, exec);
		exec->files[1] = output_redirect(current, exec);
		executor_router(current->command, exec);
		return (1);
	}
	else
		return (0);
}

static int	check_errors(t_exec *exec, int i)
{
	if (msh_inf()->quit)
		return (exit_executor(exec, -1), 1);
	exec->pids[i] = fork();
	if (exec->pids[i] < 0)
		exit_executor(exec, 1);
	return (0);
}

static void	child_routine(t_commands *current, t_exec *exec)
{
	char	*valid_path;

	if (exec->files[0] == -2 || exec->files[1] == -2)// if there was an error opening the input or output file
		exit_executor(exec, 1);
	if (current->command && !is_builtin(current->command))//if the command exists and it's not a built-in
	{
		valid_path = check_valid_command(current->command[0], exec);//checks if the command is a valid path
		if (!valid_path)
			exit_executor(exec, 127);// 127 command not found
		free(valid_path);
	}
	if (exec->next_fd[1] != -1)
		dup2(exec->next_fd[1], STDOUT_FILENO);// redirects stdout to the write end of the pipe
	if (exec->fd[0] != -1)
		dup2(exec->fd[0], STDIN_FILENO); // redirects stdin to the read end of the pipe
	if (exec->files[0] != -1)
		dup2(exec->files[0], STDIN_FILENO);// redirects stdin to the input file
	if (exec->files[1] != -1)
		dup2(exec->files[1], STDOUT_FILENO);// redirects stdout to the output file
	exit_executor(exec, -1);
	executor_router(current->command, exec);
}

static int	do_commands(t_commands *current, t_exec *exec)
{
	int	i;

	i = 0;
	while (current)
	{
		signal(SIGINT, signal_handler_child);
		init_fds(&exec->next_fd, &exec->files);// sets the ends of the pipes to -1, indicating that they are not open
		if (current->next)// if there is a next command in the pipeline
			if (pipe(exec->next_fd) < 0)// creates a pipe
				exit_executor(exec, 1);// if pipe fails, exit
		exec->files[0] = input_redirect(current, exec);
		exec->files[1] = output_redirect(current, exec);
		if (check_errors(exec, i))// checks for user interrupts or errors
			return (0);
		if (exec->pids[i++] == 0)// if we are in the child process
			child_routine(current, exec);//sets up the child’s file descriptors (e.g., redirecting stdin/stdout to pipes or files) and executes the command (either a built-in or an external program via execve).
		close_pipe_ends(exec->fd);// closes the ends of the previous pipe
		close_pipe_ends(exec->files);// closes the input and output files
		exec->fd[0] = exec->next_fd[0];// sets the read end of the current pipe to the read end of the next pipe
		exec->fd[1] = exec->next_fd[1];// sets the write end of the current pipe to the write end of the next pipe
		current = current->next;// moves to the next command
	}
	return (close_pipe_ends(exec->next_fd), 1);// closes the ends of the last pipe and returns 1 to indicate success
}

/**@brief This is the main function to execute the commands.
 * @param commands A pointer to the commands to be executed.
 * @return Void.
 */
void	executor(t_commands **commands)
{
	t_commands	*current;//points to the current command
	t_exec		exec;//execution structure
	int			i;//index to iterate through the pids
	int			status;

	current = *commands;//points to the first command
	if (do_multable_builtin(current, &exec))//checks if the command is a builtin, if so no execution is needed. "&" lets the function modify the original pointer.
		return ;
	exec.pids = malloc(sizeof(int) * msh_inf()->num_of_commands);//allocates memory for the pids and will be used later to waitpid() each child.
	init_fds(&exec.fd, NULL);//initialization of the file descriptors
	if (!do_commands(current, &exec))//Executes the parsed commands. If error occurs, it returns.
		return ;
	i = 0;
	while (i < msh_inf()->num_of_commands)
	{
		waitpid(exec.pids[i++], &status, 0);
		msh_inf()->exit_status = (status >> 8) & 0xFF;//correctly sets the exit status given by the child process.
		if (msh_inf()->sig_int)
			msh_inf()->exit_status = 130;
		else if (msh_inf()->sig_quit)
			msh_inf()->exit_status = 131;
		msh_inf()->sig_int = 0;
		msh_inf()->sig_quit = 0;
	}
	free(exec.pids);
}
