/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:48:56 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/22 09:54:04 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	char	*buffer;
	int		buffer_size;

	buffer_size = 100;
	buffer = (char *)malloc(sizeof(char) * buffer_size + 1);
	if (!buffer)
		return (1);
	getcwd(buffer, buffer_size);
	printf("%s", buffer);
	return(0);
}