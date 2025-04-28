/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:53:29 by tiade-al          #+#    #+#             */
/*   Updated: 2025/04/27 23:26:41 by tiade-al         ###   ########.fr       */
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

# define DQUOTE '\x10' // For "
# define SQUOTE '\x11' // For '
# define SPACE_MARKER '\x12' // For ' '
# define PIPE_MARKER '\x13' // For |
# define LESS_MARKER '\x14' // For <
# define GREAT_MARKER '\x15' // For >
# define LESSER_MARKER '\x14\x14' // For <<
# define GREATER_MARKER '\x15\x15' // For >>


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
	int			sig_int;		// Stores the signal interrupt status (ctrl+c)
	int			sig_quit;		// Stores the signal quit status (ctrl+\)
	int			quit;			// Stores the quit status
	int			pid;			// Stores the process ID
	int			interactive;	// Stores the interactive status
	t_commands	*commands;	// Pointer to the first command in the linked list
}		t_msh;

/* ------------------INIT------------------- */
void	minishell_init(char **env);
t_msh	*msh_inf(void);

/* ------------------BUILT-INS------------------- */
void	add_new_env_var(char *arg, char ***env_ptr);
void	copy_env_array(char **env, char **env_copy, int count);
void	print_sorted_env(char **env_copy, int fd);
int		find_env_index(char **env, const char *token);
void	ft_echo(char **cmd, int fd);
void	ft_cd(char **cmd, int fd);
void	ft_pwd(int fd);
void	ft_export(char **arg, int fd);
void	ft_unset(char **token);
void	ft_env(char **arg, int fd);
void	ft_exit(char **command, long status);
int		is_builtin(char **command);

/* ------------------EXECUTION------------------- */
void	close_pipe_ends(int *fd);
int		input_redirect(t_commands *current, t_exec *exec);
int		output_redirect(t_commands *current, t_exec *exec);
void	executor_router(char **command, t_exec *exec);
void	sig_for_heredoc(int sig);
void	executor(t_commands **commands);

/* ------------------EXPANSION------------------- */
char	*expand_env_vars(const char *str);

/* ------------------HELPERS------------------- */
void	free_array(char **args);
void	free_structs(void);
void	clean_all(void);
void	free_double_array(char **array);
void	init_fds(int (*fd1)[2], int (*fd2)[2]);
void	close_fd(int fd);
void	signal_handler_child(int sig);
int		is_valid_identifier(char *str);
char	*check_valid_command(char *command, t_exec *exec);
int		handle_invalid_identifier(char *arg, int fd, char *equal_sign);
void	signal_handler_main(int sig);
void	exit_executor(t_exec *exec, int exit_status);
void	redirect_error(char *file);
void	print_error(char *value, char *message);

/* ------------------PARSER------------------- */
int			is_redirection(char *str);
int			is_whitespace(int c);
void		free_commands(t_commands *stack);
int			find_errors(char *new);
char		**get_command(char **command);
char		**get_great(char **command);
char		*get_less(char **command);
char		**get_input_files(char **str, char *c);
char		**get_output_files(char **str);
void		parser(char *input);
int			get_process(void);
void		signal_handler_heredoc(int sig);
void		read_input(char *input);
char		*lexer(char *input);


#endif