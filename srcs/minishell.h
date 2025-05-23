/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:53:29 by tiade-al          #+#    #+#             */
/*   Updated: 2025/05/21 02:19:09 by tiade-al         ###   ########.fr       */
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
# include "../inc/Libft/libft.h"

typedef struct s_commands
{
	char				**command;
	char				**outfiles;
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
	int			exit_status;
	char		**env;
	char		**export;
	int			line_nbr;
	int			num_of_commands;
	int			sig_int;
	int			sig_quit;
	int			quit;
	int			pid;
	int			interactive;
	t_commands	*commands;
}		t_msh;

/* ------------------INIT------------------- */
t_msh	*msh_inf(void);
void	cpy_env(char **env);
void	init_vars(int *a, int *b, int *c);

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
bool	echonflag(char *str);
void	sort_env(char **env, int size);
int		env_find(char *key, char **env);
int		set_env_var(char *arg, int fd);
void	update_export(char *key, char *new_var, char *equal_sign);
int		count_strs(char **strs);

/* ------------------EXECUTION------------------- */
void	close_pipe_ends(int *fd);
int		input_redirect(t_commands *current, t_exec *exec);
int		output_redirect(t_commands *current, t_exec *exec);
void	executor_router(char **command, t_exec *exec);
void	sig_for_heredoc(int sig);
void	executor(t_commands **commands);
void	redirect_io(int file, int std);
int		check_errors(t_exec *exec, int i);

/* ------------------EXPANSION------------------- */
void	expand_heredoc(char **str);
char	**expander(char **str);
void	handle_quoted_expansion(char *str);
char	**ft_cp_double_str(char **strs);
void	edit_str(char **str);
char	*expand_variable(char *result, char *temp, int *i);
char	*copy_before_dollar(char *result, char *temp, int i);
void	fill_expansion(char *result, char *temp, char *add, int size);
int		need_expansion(char **strs);
int		str_w_space(char *str);
char	**split_by_spaces(char **strs, int index);
char	**rm_empty_str(char **strs);
char	**rm_quotes(char **strs);
char	*append_remaining(char *result, char *temp);
char	**expand_variables(char **str, int *f);

/* ------------------HELPERS------------------- */
void	free_array(char **args);
void	free_double_array(char **array);
void	init_fds(int (*fd1)[2], int (*fd2)[2]);
void	close_fd(int fd);
void	signal_handler_child(int sig);
int		is_valid_identifier(char *str);
char	*check_valid_command(char *command, t_exec *exec);
int		handle_invalid_identifier(char *arg, int fd);
void	signal_handler_main(int sig);
void	exit_executor(t_exec *exec, int exit_status);
void	redirect_error(char *file);
void	print_error(char *value, char *message);

/* ------------------PARSER------------------- */
int		is_redirection(char *str);
int		is_whitespace(int c);
void	free_commands(t_commands *stack);
int		find_errors(char *new);
char	**get_command(char **command);
char	**get_great(char **command);
char	*get_less(char **command);
char	**get_input_files(char **str, char *c);
char	**get_output_files(char **str);
void	parser(char *input);
int		get_process(void);
void	read_input(char *input);
char	*lexer(char *input);

/* ------------------Signals------------------- */
void	signal_handler_child(int sig);
void	signal_handler_main(int sig);
void	sig_for_heredoc(int sig);

char	*get_var_name(char *str);
char	*add_expansion(char **new_str, char *add, int size);
char	*expand_var(char *str);
char	*get_env_key(char *variable);
char	*ft_strndup(char const *s1, unsigned int n);

// '\2' =   = SPACE
// '\3' = | = PIPE
// '\4' = " = DQUOTES
// '\5' = ' = SQUOTES
// '\6' = > = GREATER
// "\6\6" = >> = APPEND
// '\7' = < = LESS
// "/7/7" = << = HEREDOC

#endif