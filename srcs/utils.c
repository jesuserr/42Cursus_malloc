/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:30:14 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/02 16:32:08 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void hex_dump(void *mem, size_t len)
{
    unsigned char *ptr = (unsigned char *)mem;

    for (size_t i = 0; i < len; i += 16) {
        printf("%p  ", ptr + i);
        for (size_t j = 0; j < 16; j++) {
            if (i + j < len) {
                printf("%02x ", ptr[i + j]);
            } else {
                printf("   ");
            }
        }
        printf(" ");
        for (size_t j = 0; j < 16; j++) {
            if (i + j < len) {
                printf("%c", ft_isprint(ptr[i + j]) ? ptr[i + j] : '.');
            }
        }
        printf("\n");
    }
}