/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:08:27 by joaoleote         #+#    #+#             */
/*   Updated: 2025/05/21 01:53:45 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_commands(t_commands *stack)
{
	t_commands	*current;
	t_commands	*temp;

	current = stack;
	while (current)
	{
		temp = current->next;
		free_double_array(current->command);
		if (current->output)
		{
			free_double_array(current->outfiles);
			free_double_array(current->output);
		}
		if (current->input)
		{
			free_double_array(current->infiles);
			free(current->input);
		}
		if (current->heredocs)
			free_double_array(current->heredocs);
		free(current);
		current = temp;
	}
}

/**@brief Extracts just a part of the command that will be executed
 * @param command recevies an array of str
 * @return a new array of str without the redirections
*/
char	**get_command(char **command)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (command[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (command[i])
	{
		if (is_redirection(command[i]) && command[i + 1])
			i = i + 2;
		else if (is_redirection(command[i]) && !command[i + 1])
			i++;
		else
			new[j++] = ft_strdup(command[i++]);
	}
	if (!j)
		return (free(new), NULL);
	else
		new[j] = NULL;
	return (new);
}

/**@brief All output redirections are switched to Markers
 * @param command An array of str
 * @return an array with just the tokens of redirections of output (> or >>)
*/
char	**get_great(char **command)
{
	char	**great;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (command[i])
		if (command[i++][0] == '\6')
			size++;
	if (!size)
		return (NULL);
	great = malloc(sizeof(char *) * (size + 1));
	if (!great)
		ft_exit(NULL, 0);
	great[size] = NULL;
	size = 0;
	i = 0;
	while (command[i])
	{
		if (command[i][0] == '\6')
			great[size++] = ft_strdup(command[i]);
		i++;
	}
	return (great);
}

/**@brief The last input redirection is saved in less
 * @param command An array of str
 * @return a str with the last redirection of input (< or <<)
*/
char	*get_less(char **command)
{
	char	*less;
	int		i;

	less = NULL;
	i = 0;
	while (command[i])
	{
		if (command[i][0] == '\7')
		{
			if (less)
				free(less);
			less = ft_strdup(command[i]);
		}
		i++;
	}
	return (less);
}
