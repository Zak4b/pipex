/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:01:14 by asene             #+#    #+#             */
/*   Updated: 2024/11/25 12:22:41 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exec_cmd(const char *cmd)
{
	static char	*envp[] = {"PATH=/usr/bin:/bin", NULL};
	static char	*newargv[] = {"/bin/sh", "-c", NULL, NULL};

	newargv[2] = (char *)cmd;
	return (execve("/bin/sh", newargv, envp));
}

void	execute_cmd1(int pipefd[], const char *cmd, const char *input_file)
{
	int	file1;

	file1 = open(input_file, O_RDONLY);
	if (file1 == -1)
	{
		perror("Erreur lors de l'ouverture de file1");
		exit(EXIT_FAILURE);
	}
	if (dup2(file1, STDIN_FILENO) == -1)
	{
		perror("Erreur dup2 file1");
		exit(EXIT_FAILURE);
	}
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("Erreur dup2 pipe écriture");
		exit(EXIT_FAILURE);
	}
	close(file1);
	close(pipefd[0]);
	close(pipefd[1]);
	exec_cmd(cmd);
	perror("Erreur execve cmd1");
	exit(EXIT_FAILURE);
}

void	execute_cmd2(int pipefd[], const char *cmd, const char *output_file)
{
	int	file2;

	file2 = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file2 == -1)
	{
		perror("Erreur lors de l'ouverture de file2");
		exit(EXIT_FAILURE);
	}
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("Erreur dup2 pipe lecture");
		exit(EXIT_FAILURE);
	}
	if (dup2(file2, STDOUT_FILENO) == -1)
	{
		perror("Erreur dup2 file2");
		exit(EXIT_FAILURE);
	}
	close(file2);
	close(pipefd[0]);
	close(pipefd[1]);
	exec_cmd(cmd);
	perror("Erreur execve cmd2");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: pipex <FILE> <COMMAND> <COMMAND> <FILE>\n", 2);
		return (EXIT_FAILURE);
	}
	if (pipe(pipe_fd) == -1)
		return (perror("Erreur lors de la création du pipe"), EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == -1)
		return (perror("Erreur lors du fork pour cmd1"), EXIT_FAILURE);
	if (pid1 == 0)
		execute_cmd1(pipe_fd, argv[2], argv[1]);
	pid2 = fork();
	if (pid2 == -1)
		return (perror("Erreur lors du fork pour cmd2"), EXIT_FAILURE);
	if (pid2 == 0)
		execute_cmd2(pipe_fd, argv[3], argv[4]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
