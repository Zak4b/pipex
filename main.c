/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:01:14 by asene             #+#    #+#             */
/*   Updated: 2024/11/16 13:37:30 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void execute_cmd1(int pipefd[], const char *input_file)
{
    int file1 = open(input_file, O_RDONLY);
    if (file1 == -1) {
        perror("Erreur lors de l'ouverture de file1");
        exit(EXIT_FAILURE);
    }
    if (dup2(file1, STDIN_FILENO) == -1) {
        perror("Erreur dup2 file1");
        exit(EXIT_FAILURE);
    }
    close(file1);
    if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
        perror("Erreur dup2 pipe écriture");
        exit(EXIT_FAILURE);
    }
    close(pipefd[0]); // Fermer l'extrémité de lecture du pipe
    close(pipefd[1]); // Fermer l'extrémité d'écriture du pipe
    char *cmd1_args[] = { "cat", NULL }; // Remplacez "cmd1" par votre commande
    if (execve("/bin/cat", cmd1_args, NULL) == -1) {
        perror("Erreur execve cmd1");
        exit(EXIT_FAILURE);
    }
}

void execute_cmd2(int pipefd[], const char *output_file)
{
    int file2 = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file2 == -1) {
        perror("Erreur lors de l'ouverture de file2");
        exit(EXIT_FAILURE);
    }
    // Rediriger stdin vers la lecture du pipe
    if (dup2(pipefd[0], STDIN_FILENO) == -1) {
        perror("Erreur dup2 pipe lecture");
        exit(EXIT_FAILURE);
    }
    close(pipefd[0]); // Fermer l'extrémité de lecture du pipe
    close(pipefd[1]); // Fermer l'extrémité d'écriture du pipe
    if (dup2(file2, STDOUT_FILENO) == -1) {
        perror("Erreur dup2 file2");
        exit(EXIT_FAILURE);
    }
    close(file2);
    char *cmd2_args[] = { "cat", NULL }; // Remplacez "cmd2" par votre commande
    if (execve("/bin/cat", cmd2_args, NULL) == -1) {
        perror("Erreur execve cmd2");
        exit(EXIT_FAILURE);
    }
}

// < file1 cmd1 | cmd2 > file2
int main(int argc, char **argv)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	(void)argc;
	if (pipe(pipe_fd) == -1)
	{
        perror("Erreur lors de la création du pipe");
        exit(EXIT_FAILURE);
    }
	pid1 = fork();
	if (pid1 == -1)
	{
        perror("Erreur lors du fork pour cmd1");
        exit(EXIT_FAILURE);
    }
    if (pid1 == 0)
		execute_cmd1(pipe_fd, argv[1]);
	if ((pid2 = fork()) == -1) {
        perror("Erreur lors du fork pour cmd2");
        exit(EXIT_FAILURE);
    }
	if (pid2 == 0)
		execute_cmd2(pipe_fd, argv[4]);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}
