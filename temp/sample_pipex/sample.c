#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_CMDS 128
#define MAX_ARGS 128

// Function to find the full path of a command using the PATH environment variable
char *find_command_path(const char *cmd, char **envp) {
    char *path_env = NULL;

    for (int i = 0; envp[i] != NULL; i++) {
        if (strncmp(envp[i], "PATH=", 5) == 0) {
            path_env = envp[i] + 5;
            break;
        }
    }

    if (path_env == NULL) {
        fprintf(stderr, "PATH environment variable not found\n");
        return NULL;
    }

    char *path = strtok(path_env, ":");
    while (path != NULL) {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, cmd);

        if (access(full_path, X_OK) == 0) {
            return strdup(full_path);
        }

        path = strtok(NULL, ":");
    }

    return NULL;
}

// Function to execute a command using execve
void execute_command(char *cmd, int input_fd, int output_fd, char **envp) {
    char *args[MAX_ARGS];
    char *token = strtok(cmd, " ");
    int i = 0;

    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    char *cmd_path = find_command_path(args[0], envp);
    if (cmd_path == NULL) {
        fprintf(stderr, "Command not found: %s\n", args[0]);
        exit(EXIT_FAILURE);
    }

    if (input_fd != STDIN_FILENO) {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }

    if (output_fd != STDOUT_FILENO) {
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);
    }

    if (execve(cmd_path, args, envp) == -1) {
        perror("execve failed");
        exit(EXIT_FAILURE);
    }
}

void create_pipeline(char *commands[], int num_cmds, int input_fd, int output_fd, char **envp) {
    int pipe_fd[2];
    int prev_fd = input_fd;

    for (int i = 0; i < num_cmds; ++i) {
        if (i < num_cmds - 1) {
            if (pipe(pipe_fd) == -1) {
                perror("pipe failed");
                exit(EXIT_FAILURE);
            }
        } else {
            pipe_fd[1] = output_fd;
        }

        pid_t pid = fork();
        if (pid == 0) {
            if (prev_fd != STDIN_FILENO) {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (pipe_fd[1] != STDOUT_FILENO) {
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }
            if (pipe_fd[0] != STDIN_FILENO) {
                close(pipe_fd[0]);
            }
            execute_command(commands[i], prev_fd, pipe_fd[1], envp);
        } else if (pid < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (prev_fd != input_fd) {
            close(prev_fd);
        }
        close(pipe_fd[1]);
        prev_fd = pipe_fd[0];
    }

    if (prev_fd != input_fd) {
        close(prev_fd);
    }
}

int main(int argc, char *argv[], char *envp[]) {
    if (argc < 5) {
        fprintf(stderr, "Usage: %s here_doc LIMITER cmd cmd_1 ... cmd_n output_file\n", argv[0]);
        fprintf(stderr, "   or: %s input_file cmd_1 ... cmd_n output_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int input_fd, output_fd;
    int heredoc_mode = strcmp(argv[1], "here_doc") == 0;

    if (heredoc_mode) {
        char *limiter = argv[2];

        // Create a pipe for passing heredoc content
        int heredoc_pipe[2];
        if (pipe(heredoc_pipe) == -1) {
            perror("pipe failed");
            exit(EXIT_FAILURE);
        }

        printf("heredoc> ");
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), stdin)) {
            if (strncmp(buffer, limiter, strlen(limiter)) == 0 && buffer[strlen(limiter)] == '\n') {
                break;
            }
            write(heredoc_pipe[1], buffer, strlen(buffer));
            printf("heredoc> ");
        }

        close(heredoc_pipe[1]); // Close write end of heredoc pipe
        input_fd = heredoc_pipe[0];
        output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    } else {
        // Non-heredoc mode
        input_fd = open(argv[1], O_RDONLY);
        if (input_fd < 0) {
            perror("Failed to open input file");
            exit(EXIT_FAILURE);
        }
        output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }

    if (output_fd < 0) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }

    // Extract commands
    char *commands[MAX_CMDS];
    int cmd_count = 0;
    for (int i = heredoc_mode ? 3 : 2; i < argc - 1; ++i) {
        commands[cmd_count++] = argv[i];
    }

    // Create the pipeline
    create_pipeline(commands, cmd_count, input_fd, output_fd, envp);

    close(input_fd);
    close(output_fd);

    while (wait(NULL) > 0);

    return 0;
}
