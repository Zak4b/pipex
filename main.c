/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:01:14 by asene             #+#    #+#             */
/*   Updated: 2024/11/25 16:09:20 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(const char *cmd, int fd_in, int fd_out)
{
	static char	*newargv[] = {"/bin/sh", "-c", NULL, NULL};

	if ((dup2(fd_in, STDIN_FILENO) == -1))
		perror("Error dup2 input");
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		perror("Error dup2 ouput");
	close(fd_in);
	close(fd_out);
	newargv[2] = (char *)cmd;
	execve("/bin/sh", newargv, NULL);
	perror("Error ");
	exit(EXIT_FAILURE);
}

pid_t	pipe_loop(int file_in, int file_out, int argc, char **argv)
{
	int			pipe_fd[2];
	pid_t		pid;
	static int	i = 1;
	int			prev_fd;

	prev_fd = file_in;
	while (++i < argc - 1)
	{
		if (i != (argc - 2) && pipe(pipe_fd) == -1)
			return (perror("Eror on pipe creation "), -1);
		pid = fork();
		if (pid == -1)
			return (perror("Eror on fork "), -1);
		if (pid == 0)
		{
			if (i == (argc - 2))
				exec_cmd(argv[i], prev_fd, file_out);
			close(pipe_fd[0]);
			exec_cmd(argv[i], prev_fd, pipe_fd[1]);
		}
		close(prev_fd);
		prev_fd = pipe_fd[0];
		close(pipe_fd[1]);
	}
	return (pid);
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		file1;
	int		file2;

	if (argc < 5)
	{
		ft_putstr_fd("Usage: pipex <FILE> <COMMAND> <COMMAND>... <FILE>\n", 2);
		exit(EXIT_FAILURE);
	}
	file1 = open(argv[1], O_RDONLY);
	if (file1 == -1)
	{
		perror("Error while opening file");
		exit(EXIT_FAILURE);
	}
	file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file2 == -1)
	{
		perror("Error while opening file");
		exit(EXIT_FAILURE);
	}
	pid = pipe_loop(file1, file2, argc, argv);
	close(file1);
	close(file2);
	waitpid(pid, NULL, 0);
}
