/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:59:18 by joaoleote         #+#    #+#             */
/*   Updated: 2025/04/26 11:49:54 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <pwd.h>
# include <stdbool.h>
# include <dirent.h>
# include "../Libft/inc/libft.h"

# define DQUOTE '\x10' // For "
# define SQUOTE '\x11' // For '
# define SPACE_MARKER '\x12' // For ' '
# define PIPE_MARKER '\x13' // For |
# define LESS_MARKER '\x14' // For <
# define GREAT_MARKER '\x15' // For >
# define LESSER_MARKER '\x14\x14' // For <<
# define GREATER_MARKER '\x15\x15' // For >>

typedef struct s_commands{
	char				**command;
	char				**gt_files;
	char				**greater_than;
	char				**heredocs;
	char				**lt_files;
	char				*less_than;
	struct s_commands	*next;
}				t_commands;

typedef struct s_msh
{
	char		*input;            // Stores the input to minishell so it can be parsed after ⤵ //beta
	char		command;        // Stores parsed command arguments <------------------------ //beta
	char		*pwd;            // Stores the current working directory
	int			exit_status;    // Stores the last command's exit status
	char		env;            // Stores environment variables
	char		**export;        // Stores environment variables to use in export 
	int			line_nbr;        // Stores the amount of lines
	int			num_of_commands;// Stores the number of commands in a pipeline
	int			interactive;
	int			sig_int;        // Stores the signal interrupt status
	int			sig_quit;        // Stores the signal quit status
	int			ctrl;
	int			quit;            // Stores the quit status
	int			pid;
	t_commands	*commands;    // Pointer to the first command in the linked list
}				t_msh;

void		free_double_array(char *array);
int			is_redirection(char *str);
int			is_whitespace(int c);
void		free_commands(t_commands *stack);
int			find_errors(char *new);
void		free_commands(t_commands *stack);
char		**get_command(char **command);
char		**get_great(char **command);
char		*get_less(char **command);
char		**get_input_files(char **str, char *c);
char		**get_output_files(char **str);
void		parser(char *input);
int			get_process(void);
t_msh		*msh_inf(void);
void		signal_handler_child(int sig);
void		signal_handler_main(int sig);
void		signal_handler_heredoc(int sig);
void		read_input(char *input);

#endif
