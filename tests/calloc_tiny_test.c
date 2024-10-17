/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:33:16 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/17 12:28:58 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int	main(void)
{
	// Simulation of adding a new heap to full TINY heap

	// Creates a TINY heap and completely fills it with 128 blocks of 128 bytes
	// to force the creation of a new one in the next allocation.
	void *array[128];	
	for (int i = 0; i < 128; i++)
	{
		array[i] = ft_malloc(128);
		ft_memset(array[i], 'A', 128);
	}	
	
	// Printing the first lines of the TINY heap, free the first block and malloc again.
	ft_hex_dump(g_heaps[TINY_HEAP], 512, 64);       // after malloc
	ft_printf("---\n");
    ft_free(array[0]);
    ft_hex_dump(g_heaps[TINY_HEAP], 512, 64);       // after free
    array[0] = ft2_calloc(128,1);
    ft_printf("---\n");
    ft_hex_dump(g_heaps[TINY_HEAP], 512, 64);       // after calloc
			
	return (0);
}

// make && ./allocator | grep "128 bytes" | wc -l -> should return 384
// make && valgrind --leak-check=full ./allocator
// make && strace ./allocator 2>&1 | grep mmap
// make && /usr/bin/time -v ./allocator 0.00
