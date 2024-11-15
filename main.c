/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:01:14 by asene             #+#    #+#             */
/*   Updated: 2024/11/15 14:53:58 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_command()
{
	pid_t pid = fork();
	if (pid == 0)
	{
		char *arg[] = {"/bin/ls", "-l", NULL};
		execve("/bin/ls", arg, NULL);
		exit(EXIT_SUCCESS);
	}
}

// < file1 cmd1 | cmd2 > file2
int main(int argc, char **argv)
{
	int	fd_in;
	//int	fd_out ;

	if (argc != 5)
		return (EXIT_FAILURE);
	if (access(argv[1], R_OK) == -1)
		perror(argv[1]);
	if (access(argv[argc - 1], W_OK) == -1)
		perror(argv[argc - 1]);
	if (errno)
		exit(EXIT_FAILURE);
	fd_in = open(argv[1], O_RDONLY);
	// read file
	close(fd_in);
	exec_command();

	return (EXIT_SUCCESS);
}
