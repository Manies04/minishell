/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:53:29 by tiade-al          #+#    #+#             */
/*   Updated: 2025/04/25 23:12:21 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <dirent.h>
# include <errno.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <limits.h>
# include <stdarg.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <errno.h>
#include "../inc/Libft/libft.h"


typedef struct s_commands //has the commands separated by the pipes
{
	char				**command;
	char				**outfiles;//File names used in > or >> redirections
	char				**output;
	char				**heredocs;
	char				**infiles;
	char				*input;
	struct s_commands	*next;
}	t_commands;

typedef struct s_exec
{
	int			next_fd[2];
	int			files[2];
	int			fd[2];
	int			*pids;
}		t_exec;

//minishell geral struct
typedef struct s_msh
{
	char		*input;			// Stores the input to minishell so it can be parsed after ⤵ //beta
	char		**command;		// Stores parsed command arguments <------------------------ //beta
	char		*pwd;			// Stores the current working directory
	int			exit_status;	// Stores the last command's exit status
	char		**env;			// Stores environment variables
	char		**export;		// Stores environment variables to use in export 
	int			line_nbr;		// Stores the amount of lines
	int			num_of_commands;// Stores the number of commands in a pipeline
	int			sig_int;		// Stores the signal interrupt status
	int			sig_quit;		// Stores the signal quit status
	int			quit;			// Stores the quit status
	t_commands	*commands;	// Pointer to the first command in the linked list
}		t_msh;

void	minishell_init(char **env);
t_msh	*msh_inf(void);
void	free_array(char **args);
void	free_structs(void);
void	clean_all(void);
void	exitwcode(int exit_code);
void	add_new_env_var(char *arg, char ***env_ptr);
int		handle_invalid_identifier(char *arg, int fd, char *equal_sign);
void	copy_env_array(char **env, char **env_copy, int count);
void	print_sorted_env(char **env_copy, int fd);
int		is_valid_identifier(char *str);
void	ft_echo(char **cmd, int fd);
void	ft_cd(char **cmd, int fd);
void	ft_pwd(int fd);
void	ft_export(char **arg, int fd);
void	ft_unset(char **token);
void	ft_env(char **arg, int fd);
void	ft_exit(char **args);
char	*expand_env_vars(const char *str);
int		input_redirect(t_commands *current, t_exec *exec);
int		output_redirect(t_commands *current, t_exec *exec);
void	executor_router(char **command, t_exec *exec);
int		find_env_index(char **env, const char *token);
void	sig_for_heredoc(int sig);
void	init_fds(int (*fd1)[2], int (*fd2)[2]);
void	close_fd(int fd);
void	close_pipe_ends(int *fd);
void	signal_handler_child(int sig);
char	*check_valid_command(char *command, t_exec *exec);





#endif