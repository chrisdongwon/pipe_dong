/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 08:53:12 by cwon              #+#    #+#             */
/*   Updated: 2024/12/30 21:49:53 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Function to add a character to the current token
void add_char(char **token, size_t *len, char c) {
    *token = realloc(*token, (*len) + 2); // Allocate space for the new character and null terminator
    if (*token == NULL) {
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    (*token)[(*len)++] = c;
    (*token)[*len] = '\0'; // Null-terminate the string
}

// Function to tokenize a command line string
char **tokenize(const char *input) {
    char **tokens = NULL;    // Array of tokens
    size_t num_tokens = 0;   // Number of tokens
    char *token = NULL;      // Current token
    size_t token_len = 0;    // Current token length
    int in_single_quote = 0; // Flag for single quotes
    int in_double_quote = 0; // Flag for double quotes

    for (const char *p = input; *p != '\0'; ++p) {
        if (*p == '\'' && !in_double_quote) {
            // Toggle single-quote mode
            in_single_quote = !in_single_quote;
        } else if (*p == '"' && !in_single_quote) {
            // Toggle double-quote mode
            in_double_quote = !in_double_quote;
        } else if (*p == '\\' && !in_single_quote) {
            // Handle backslashes
            ++p; // Skip the backslash
            if (*p != '\0') {
                add_char(&token, &token_len, *p);
            }
        } else if (isspace(*p) && !in_single_quote && !in_double_quote) {
            // Token separator
            if (token_len > 0) {
                // Add the current token to the token list
                tokens = realloc(tokens, (num_tokens + 1) * sizeof(char *));
                if (tokens == NULL) {
                    perror("realloc");
                    exit(EXIT_FAILURE);
                }
                tokens[num_tokens++] = token;
                token = NULL;
                token_len = 0;
            }
        } else {
            // Normal character
            add_char(&token, &token_len, *p);
        }
    }

    // Add the final token (if any)
    if (token_len > 0) {
        tokens = realloc(tokens, (num_tokens + 1) * sizeof(char *));
        if (tokens == NULL) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        tokens[num_tokens++] = token;
    }

    // Null-terminate the token list
    tokens = realloc(tokens, (num_tokens + 1) * sizeof(char *));
    if (tokens == NULL) {
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    tokens[num_tokens] = NULL;

    return tokens;
}

// Free the tokenized list
void free_tokens(char **tokens) {
    if (tokens) {
        for (size_t i = 0; tokens[i] != NULL; ++i) {
            free(tokens[i]);
        }
        free(tokens);
    }
}

char	**tokenize(t_pipex *param, char *cmd)
{
	char	**result;

	result = protected_split(param, cmd, ' ');
	if (!result[0])
	{
		flush_str_array(result);
		return (whitespace_command(param, cmd));
	}
	return (result);
}
