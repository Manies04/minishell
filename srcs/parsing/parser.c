/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:06:52 by joaoleote         #+#    #+#             */
/*   Updated: 2025/05/05 00:17:12 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**@brief Create and allocate the command data.
 * @param command the user command splitted.
 * @return new command struct node.
 */
static t_commands	*new_command(char *command)
{
	char		**splitted; //array of str with the command tokens
	t_commands	*new; //pointer to a new struct

	new = malloc(sizeof(t_commands)); //Alocates memory
	if (!new) //Verifications
		return ((void *)0);
	splitted = ft_split(command, '\2'); //Divides the str command using Spaces
	splitted = expander(splitted); //Aplies variable expansions to command tokens
	new->output = get_great(splitted); //Extracts all redirections > or >> and keeps
	new->input = get_less(splitted); //Gets the last redirection of input found
	new->outfiles = get_output_files(splitted); //Returns all the assossiated files to the output redirections
	new->infiles = get_input_files(splitted, "\7"); //returns all assossiated files input redirections
	new->heredocs = get_input_files(splitted, "\7\7"); // returns the limiters of the heredocs
	new->command = get_command(splitted); //Extracts just the real commands and argumments
	new->next = (void *)0; //initializes the pointer next has NULL
	free_double_array(splitted); //frees the array splitted 
	return (new); //returns the pointer to a new struct
}

/**@brief Adds the command node to the linked list.
 * @param lst First element of the list.
 * @param command the command to stract the data.
 */
static void	add_next_command(t_commands **lst, char *command)
{
	t_commands	*current; //Used to run the list till the finish
	
	if (!(*(lst))) //if the list is empty
	{
		*(lst) = new_command(command); //Creates a new command e puts it in the sorce of the code
		return ; //returns imidiately
	}
	current = *(lst); //Starts to run the list through the 1st element
	while (current->next) //Finds the last node
		current = current->next;
	current->next = new_command(command); //Creates a new node with the command and connects to the end of the lists
}

void	parser(char *input)
{
	char	**splitted; //array of str with the commands splitted by pipe
	int		i; //index to run the array

	i = 0; //initializes the counter 
	if (!ft_strchr(input, '\3')) //Verifies if there arent any pipes
		add_next_command(&msh_inf()->commands, input); //adds directly the command to the list
	else //if theres any pipes
	{
		splitted = ft_split(input, '\3'); //dives the input str with a pipe, separating the commans of the pipeline
		while (splitted[i]) //for each separate command, adds it to the list via add_next_command
			add_next_command(&msh_inf()->commands, splitted[i++]);
		free_double_array(splitted); //frees the memory used
	}
	if (i == 0) //makes sure that i is at least 1
		i = 1;
	msh_inf()->num_of_commands = i; //updates the number of commans of the global shell struct
}
