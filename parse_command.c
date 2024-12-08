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
    char **tokens = NULL;
    char *current_token = NULL;
    int in_single_quote = 0, in_double_quote = 0;

    *token_count = 0;

    while (*ptr) {
        if (isspace(*ptr) && !in_single_quote && !in_double_quote) {
            // Finalize the current token if outside quotes
            if (current_token) {
                tokens = realloc(tokens, (*token_count + 1) * sizeof(char *));
                tokens[*token_count] = strdup(current_token);
                (*token_count)++;
                free(current_token);
                current_token = NULL;
            }
        } else if (*ptr == '\'' && !in_double_quote) {
            // Toggle single quotes
            in_single_quote = !in_single_quote;
        } else if (*ptr == '"' && !in_single_quote) {
            // Toggle double quotes
            in_double_quote = !in_double_quote;
        } else {
            // Append the character to the current token
            size_t current_length = current_token ? strlen(current_token) : 0;
            current_token = realloc(current_token, current_length + 2);  // +2 for the new char and null terminator
            current_token[current_length] = *ptr;
            current_token[current_length + 1] = '\0';
        }
        ptr++;
    }

    // Finalize the last token
    if (current_token) {
        tokens = realloc(tokens, (*token_count + 1) * sizeof(char *));
        tokens[*token_count] = strdup(current_token);
        (*token_count)++;
        free(current_token);
    }

    return tokens;
}
