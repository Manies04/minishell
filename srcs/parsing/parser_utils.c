/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:08:27 by joaoleote         #+#    #+#             */
/*   Updated: 2025/04/30 17:19:31 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_commands(t_commands *stack)
{
	t_commands	*current; //points to the current node
	t_commands	*temp; //is to keep the next node before frees the current

	current = stack; //initializes current with the 1st element of the list
	while (current)
	{
		temp = current->next; //keeps the next node in temp
		free_double_array(current->command); //frees the array of str command that represents the command and his argumments
		if (current->output) //checks if theres any output redirections >
		{
			free_double_array(current->outfiles); //frees outfiles(name of the files to redirect)
			free_double_array(current->output); //frees output (> or >>)
		}
		if (current->input) //checks if theres any input redirections <
		{
			free_double_array(current->infiles); //frees infiles(read files)
			free(current->input); //frees input(< or <<)
		}
		if (current->heredocs) //if theres any heredocs(<<)
			free_double_array(current->heredocs); //frees them
		free(current); //frees the current node
		current = temp; //Goes to the next node of the list using temp
	}
}

/**@brief Extracts just a part of the command that will be executed
 * @param command recevies an array of str
 * @return a new array of str without the redirections
*/
char	**get_command(char **command)
{
	char	**new; //the array where will be keeped the free commands
	int		i; //index to run through the original array
	int		j; //index to fill the array new

	i = 0;
	j = 0;
	while (command[i]) //counts how many str are in the command
		i++;
	new = malloc(sizeof(char *) * (i + 1)); //Allocates memory to new new array with i and +1 to NULL
	i = 0; //reinitiates i to start again the loop
	while (command[i]) //Runs though all elements of the command array
	{
		if (is_redirection(command[i]) && command[i + 1]) //if the actual character is a redirection and the next is an argument
			i = i + 2; //Advances 2 positions(jumps through the redirection and the file name)
		else if (is_redirection(command[i]) && !command[i + 1]) //if theres any redirection alone at the end 
			i++; //Advances just 1 position
		else
			new[j++] = ft_strdup(command[i++]); //If it isnt any redirections copies the str to new[j]
	}
	if (!j) //if there arent any arguments keeps, frees new and returns NULL
		return (free(new), NULL);
	else
		new[j] = NULL; //otherwise, new[j] is equaled to NULL to finish
	return (new);
}

/**@brief All output redirections are switched to Markers
 * @param command An array of str
 * @return an array with just the tokens of redirections of output (> or >>)
*/
char	**get_great(char **command)
{
	char	**great; //new array with redirections found
	int		i; //index to command
	int		size; //number of found redirections

	i = 0;
	size = 0;
	while (command[i])
		if (command[i++][0] == '\6') //if the 1st character is a Marker increments size
			size++;
	if (!size) //if there wasn't any Marker, function returns NULL
		return (NULL);
	great = malloc(sizeof(char *) * (size + 1)); //Alocates memory with space to str and \0
	if (!great) //if the alocation fails calls ft_exit, to exit the program
		ft_exit(NULL, 0);
	great[size] = NULL; //Make sure that great finishes with NULL
	size = 0; //Reinitializes the index to rerun the array
	i = 0; //Reinitializes the index to rerun the array
	while (command[i]) //Runs the array command
	{
		if (command[i][0] == '\6') //Everytime he founds an token starting with a marker
			great[size++] = ft_strdup(command[i]); //makes a copy and adds to the array great
		i++;
	}
	return (great); //returns great just having the output redirections
}

/**@brief The last input redirection is saved in less
 * @param command An array of str
 * @return a str with the last redirection of input (< or <<)
*/
char	*get_less(char **command)
{
	char	*less; //pointer to keep the redirection of input
	int		i; //index to run through
	
	less = NULL; //initializes with NULL
	i = 0; //initializes with 0
	while (command[i]) //while command
	{
		if (command[i][0] == '\7') //if the first character of the command is a marker
		{
			if (less) //if less already has an redirection saved
				free(less); //it frees it
			less = ft_strdup(command[i]); //makes a copy of the current last redirection to less
		}
		i++;
	}
	return (less); //returns the last redirection found
}
