/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:46:33 by cwon              #+#    #+#             */
/*   Updated: 2024/12/08 14:09:26 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parse_command(char *command)
{
	char	**result;
	int		single_quote;
	int		double_quote;
	
	while (*command)
	{
		//STUB
		command++;
	}
	// TODO: get last token
	return (result);
}

char **tokenize(const char *command, int *token_count) {
    const char *ptr = command;
    char *current_token = NULL;
    size_t token_length = 0;
    int in_single_quote = 0, in_double_quote = 0;
    TokenNode *head = NULL;

    while (*ptr) {
        if (isspace(*ptr) && !in_single_quote && !in_double_quote) {
            // Finalize the current token if outside quotes
            if (current_token) {
                current_token[token_length] = '\0';
                head = add_token(head, current_token);
                free(current_token);
                current_token = NULL;
                token_length = 0;
            }
        } else if (*ptr == '\'' && !in_double_quote) {
            // Toggle single quotes
            in_single_quote = !in_single_quote;
        } else if (*ptr == '"' && !in_single_quote) {
            // Toggle double quotes
            in_double_quote = !in_double_quote;
        } else {
            // Append the character to the current token
            current_token = realloc(current_token, token_length + 2);  // +2 for new char and null terminator
            current_token[token_length++] = *ptr;
            current_token[token_length] = '\0';
        }
        ptr++;
    }

    // Finalize the last token
    if (current_token) {
        head = add_token(head, current_token);
        free(current_token);
    }

    // Convert the linked list to an array
    char **result = convert_to_array(head, token_count);

    // Free the linked list
    free_token_list(head);

    return result;
}
