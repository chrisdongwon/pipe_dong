/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:07:49 by cwon              #+#    #+#             */
/*   Updated: 2025/01/09 14:46:14 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// int prev_fd = -1;

// // Open input file for reading
// int input_fd = open(input_file, O_RDONLY);
// if (input_fd < 0) {
// perror("Failed to open input file");
// exit(1);
// }

// // Open output file for writing
// int output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// if (output_fd < 0) {
// perror("Failed to open output file");
// close(input_fd);
// exit(1);
// }

// for (int i = 0; i < num_commands; i++) {
// if (i < num_commands - 1) {
//     // Create a pipe for the next command
//     if (pipe(pipe_fds) < 0) {
// 	perror("Pipe failed");
// 	exit(1);
//     }
// }

// pid_t pid = fork();
// if (pid < 0) {
//     perror("Fork failed");
//     exit(1);
// }

// if (pid == 0) { // Child process
//     if (i == 0) {
// 	// Redirect input for the first command
// 	dup2(input_fd, STDIN_FILENO);
// 	close(input_fd);
//     } else {
// 	// Redirect input to previous pipe
// 	dup2(prev_fd, STDIN_FILENO);
// 	close(prev_fd);
//     }

//     if (i < num_commands - 1) {
// 	// Redirect output to the current pipe
// 	dup2(pipe_fds[1], STDOUT_FILENO);
// 	close(pipe_fds[0]);
// 	close(pipe_fds[1]);
//     } else {
// 	// Redirect output to the output file
// 	dup2(output_fd, STDOUT_FILENO);
// 	close(output_fd);
//     }

//     // Execute the command
//     char *cmd[] = {"/bin/sh", "-c", commands[i], NULL};
//     execvp(cmd[0], cmd);

//     // If execvp fails
//     perror("Exec failed");
//     exit(1);
// } else { // Parent process
//     if (i > 0) {
// 	close(prev_fd);
//     }

//     if (i < num_commands - 1) {
// 	close(pipe_fds[1]);
// 	prev_fd = pipe_fds[0];
//     }
// }
// }

// close(input_fd);
// close(output_fd);

static void	exec_cmd(t_pipex *param, ssize_t i)
{
	if (!i)
	{
		if (access(param->input_file, R_OK) == -1 && errno == EACCES)
			perror_exit(param, "no read permission on input file", 1);
		protected_dup2(param, param->input_fd, STDIN_FILENO);
	}
	else
	{

	}
	if (i < param->arg_count - 1)
	{

	}
	else
	{
		if (access(param->output_file, W_OK) == -1 && errno == EACCES)
			perror_exit(param, "no write permission on output file", 1);
		protected_dup2(param, param->pipefd[0], STDIN_FILENO);
	}
}

void	pipex(int argc, char **argv)
{
	t_pipex	param;
	ssize_t	i;

	init_pipex(&param, argc, argv);
	i = -1;
	while (++i < param.arg_count)
	{
		protected_pipe(&param);
		param.arg_array[i].pid = protected_fork(&param);
		if (!param.arg_array[i].pid)
			exec_cmd(&param, i);
	}
	flush_pipex(&param);
	i = -1;
	while(++i < param.arg_count)
		param.arg_array[i].pid = waitpid(param.arg_array[i].pid, &param.arg_array[i].status, 0);
	if (WEXITSTATUS(param.arg_array[i].status))
		exit(WEXITSTATUS(param.arg_array[i].status));
}

int	main(int argc, char **argv)
{
	pipex(argc, argv);
	return (0);
}
