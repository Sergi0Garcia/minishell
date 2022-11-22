/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:48:56 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/22 14:36:45 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// int main(int argc, char **argv, char **env)
// {
// 	char	*buffer;
// 	int		buffer_size;
// 	char	*arg[2];

// 	printf("env:%s\n", env[1]);
// 	buffer_size = 100;
// 	buffer = (char *)malloc(sizeof(char) * buffer_size + 1);
// 	if (!buffer)
// 		return (1);
// 	getcwd(buffer, buffer_size);
// 	printf("strcmp: %i\n", strcmp(argv[1], "cat"));
// 	arg[0] = "/bin/bash ls";
// 	arg[1] = "-lh";
// 	printf("Here\n");
// 	execve(arg[0], arg, NULL);
// 	printf("\n");
// 	printf("buffer: %s\n", buffer);
// 	printf("i: %i\n", argc);
// 	return(0);
// }

// int main(int argc, char **argv, char **envp)
// {
// 	char *args[4];
// 	int res;
// 	int i;

// 	(void)argc;
// 	(void)argv;

// 	i = 0;
// 	printf("ENV\n");
// 	while(envp[i])
// 	{
// 		printf("%s\n", envp[i]);
// 		i++;
// 	}
// 	args[0] = "ls";
// 	args[1] = "-la";
// 	args[2] = "/Users/segarcia/Documents/42/minishell";
// 	args[3] = NULL;
// 	res = execve("/bin/ls", args, NULL);
// 	printf("res: %i\n", res);
// }

// int	ft_pwd(void)
// {
// 	char	buffer[4096];

// 	if (getcwd(buffer, 4096))
// 	{
// 		printf("%s", buffer);
// 		write(1, "\n", 1);
// 		return (EXIT_SUCCESS);
// 	}
// 	else
// 		return (EXIT_FAILURE);
// }

// int main(void)
// {
// 	ft_pwd();
// }