/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:30:14 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/04 16:22:11 by jesuserr         ###   ########.fr       */
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
		ft_printf("%s%p:  ", BLUE, ptr + i);
		for (size_t j = 0; j < bytes_per_line; j++)
		{
			if (ptr[i + j] == 0)
				ft_printf("%s", GREY);
			else
				ft_printf("%s", LIGHT_WHITE);
			print_hex_bytes(ptr[i + j]);
			if (j % 8 == 7)
				ft_printf(" ");
		}
		ft_printf(" ");
		for (size_t j = 0; j < bytes_per_line; j++)
		{
			ft_printf("%s%c", BLUE, ft_isprint(ptr[i + j]) ? ptr[i + j] : '.');
			if (j % 8 == 7)
				ft_printf(" ");
		}
		ft_printf("\n%s", RESET);
	}
}

// Print byte in hexadecimal format
// hex_case = 55 for uppercase (87 for lowercase)
void	print_hex_bytes(unsigned char byte)
{
	unsigned char	hex_case;

	hex_case = 87;
	if ((byte >> 4) < 10)
		ft_printf("%c", (byte >> 4) + 48);
	else
		ft_printf("%c", (byte >> 4) + hex_case);
	if ((byte & 0x0F) < 10)
		ft_printf("%c ", (byte & 0x0F) + 48);
	else
		ft_printf("%c ", (byte & 0x0F) + hex_case);
}
