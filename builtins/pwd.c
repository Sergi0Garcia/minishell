/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:48:56 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/22 12:29:04 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv, char **env)
{
	char	*buffer;
	int		buffer_size;
	char	*arg[2];

	printf("env:%s\n", env[1]);
	buffer_size = 100;
	buffer = (char *)malloc(sizeof(char) * buffer_size + 1);
	if (!buffer)
		return (1);
	getcwd(buffer, buffer_size);
	printf("strcmp: %i\n", strcmp(argv[1], "cat"));
	arg[0] = "/bin/bash ls";
	arg[1] = "-lh";
	printf("Here\n");
	execve(arg[0], arg, NULL);
	printf("\n");
	printf("buffer: %s\n", buffer);
	printf("i: %i\n", argc);
	return(0);
}

// int main()
// {
// 	char *args[3];
// 	int res;

// 	args[0] = "/bin/bash";
// 	args[1] = "cat";
// 	args[2] = "./";
// 	res = execve("/bin/bash", args, NULL);
// 	printf("res: %i\n", res);
// }