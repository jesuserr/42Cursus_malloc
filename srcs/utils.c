/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:30:14 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/04 14:18:26 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// Casts void * to unsigned char * to access memory at byte level
void	hex_dump(void *mem, size_t len, size_t bytes_per_line)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)mem;
	for (size_t i = 0; i < len; i += bytes_per_line)
	{
		printf("%s%p:  ", BLUE, ptr + i);
		for (size_t j = 0; j < bytes_per_line; j++)
		{
			if (ptr[i + j] == 0)
				printf("%s", GREY);
			else
				printf("%s", LIGHT_WHITE);
			printf("%02x ", ptr[i + j]);
			if (j % 8 == 7)
				printf(" ");
		}
		printf(" ");
		for (size_t j = 0; j < bytes_per_line; j++)
		{
			printf("%s%c", BLUE, ft_isprint(ptr[i + j]) ? ptr[i + j] : '.');
			if (j % 8 == 7)
				printf(" ");
		}
		printf("\n%s", RESET);
	}
}
