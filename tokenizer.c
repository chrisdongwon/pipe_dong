/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 08:53:12 by cwon              #+#    #+#             */
/*   Updated: 2025/01/01 19:23:41 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	parse_single(char c, char *buffer, t_tokenizer *data)
{
	if (c == '\'')
		data->single_quote = 0;
	else
		buffer[data->j++] = c;
}

static void	parse_double(char c, char *buffer, t_tokenizer *data)
{
	if (c == '"')
		data->double_quote = 0;
	else if (c == '\\')
	{
		if (++data->i < data->len)
		{
			c = data->str[data->i];
			buffer[data->j++] = c;
		}
	}
	else
		buffer[data->j++] = c;
}

static void	parse_token(char c, char *buffer, t_tokenizer *data, t_list **node)
{
	if (ft_isspace(c))
	{
		if (data->j)
		{
			buffer[data->j] = 0;
			append_token(node, buffer);
			data->j = 0;
		}
	}
	else if (c == '\'')
		data->single_quote = 1;
	else if (c == '"')
		data->double_quote = 1;
	else if (c == '\\')
	{
		if (++data->i < data->len)
		{
			c = data->str[data->i];
			buffer[data->j++] = c;
		}
	}
	else
		buffer[data->j++] = c;
}

static t_list	*parse(char *input)
{
	t_list		*node;
	char		c;
	char		buffer[1024];
	t_tokenizer	data;

	init_tokenizer(&node, &data, input);
	while (data.i < data.len)
	{
		c = input[data.i];
		if (data.single_quote)
			parse_single(c, buffer, &data);
		else if (data.double_quote)
			parse_double(c, buffer, &data);
		else
			parse_token(c, buffer, &data, &node);
		data.i++;
	}
	if (data.j)
	{
		buffer[data.j] = 0;
		append_token(&node, buffer);
	}
	return (node);
}

char	**tokenize(t_pipex *param, char *cmd)
{
	char	**result;
	t_list	*node;

	if (whitespace_command(cmd))
	{
		result = (char **)malloc(2 * sizeof(char *));
		if (!result)
			error_exit(param, "tokenize() failed", 1);
		result[0] = protected_strdup(param, cmd);
		result[1] = 0;
		return (result);
	}
	node = parse(cmd);
	if (!node)
		error_exit(param, "tokenize() failed", 1);
	result = list_to_array(node);
	ft_lstclear(&node, free);
	if (!result)
		error_exit(param, "tokenize() failed", 1);
	return (result);
}








#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_BUFFER_SIZE 64

typedef struct {
    char **argv;   // Array of arguments
    size_t argc;   // Number of arguments
} TokenizerResult;

// Function to dynamically resize the buffer
char *resize_buffer(char *buffer, size_t *capacity) {
    *capacity *= 2;
    buffer = realloc(buffer, *capacity);
    if (!buffer) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    return buffer;
}

// Function to tokenize the input string
TokenizerResult tokenize(const char *input) {
    size_t capacity = INITIAL_BUFFER_SIZE;
    char *buffer = malloc(capacity); // Buffer to store the current token
    if (!buffer) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    TokenizerResult result = {NULL, 0};
    size_t buf_len = 0; // Current token length
    int in_single_quotes = 0, in_double_quotes = 0;
    const char *p = input;

    while (*p) {
        if (*p == '\'' && !in_double_quotes) { // Single quote
            in_single_quotes = !in_single_quotes;
        } else if (*p == '"' && !in_single_quotes) { // Double quote
            in_double_quotes = !in_double_quotes;
        } else if (*p == '\\' && !in_single_quotes) { // Escape character
            p++; // Skip the backslash
            if (*p) {
                if (buf_len + 1 >= capacity) {
                    buffer = resize_buffer(buffer, &capacity);
                }
                buffer[buf_len++] = *p; // Add escaped character
            }
        } else if (isspace(*p) && !in_single_quotes && !in_double_quotes) { // Space (token delimiter)
            if (buf_len > 0) {
                buffer[buf_len] = '\0';
                result.argv = realloc(result.argv, sizeof(char *) * (result.argc + 1));
                result.argv[result.argc++] = strdup(buffer);
                buf_len = 0; // Reset buffer
            }
        } else { // Regular character
            if (buf_len + 1 >= capacity) {
                buffer = resize_buffer(buffer, &capacity);
            }
            buffer[buf_len++] = *p;
        }
        p++;
    }

    // Add the last token if there's any
    if (buf_len > 0) {
        buffer[buf_len] = '\0';
        result.argv = realloc(result.argv, sizeof(char *) * (result.argc + 1));
        result.argv[result.argc++] = strdup(buffer);
    }

    free(buffer);
    return result;
}

// Free memory used by TokenizerResult
void free_tokenizer_result(TokenizerResult *result) {
    for (size_t i = 0; i < result->argc; i++) {
        free(result->argv[i]);
    }
    free(result->argv);
}

// Test the tokenizer
int main() {
    const char *input = "echo \"hello world\" 'this is a test' \\$HOME path\\ with\\ spaces";
    TokenizerResult result = tokenize(input);

    printf("Tokenized arguments (%lu):\n", result.argc);
    for (size_t i = 0; i < result.argc; i++) {
        printf("[%s]\n", result.argv[i]);
    }

    free_tokenizer_result(&result);
    return 0;
}
