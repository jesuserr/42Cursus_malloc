/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:33:16 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/11 18:03:22 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int	main(void)
{
	// Simulation of adding two new heaps to full TINY heap and freeing later.

	// Creates a TINY heap and completely fills it with 128 blocks of 128 bytes
	// to force the creation of a new one in the next allocation.
	void *array[128];	
	for (int i = 0; i < 128; i++)
	{
		array[i] = ft_malloc(128);
		ft_memset(array[i], 'A', 128);
	}	
	
	// An extension of the TINY heap will be made and the previous process
	// repeated again.
	void *tmp1;
	(void)tmp1;
	void *array2[128];
	for (int i = 0; i < 128; i++)
	{
		array2[i] = ft_malloc(128);
		if (i == 0)
			tmp1 = array2[i];
		ft_memset(array2[i], 'B', 128);
	}
	
	// Another extension of the TINY heap and another complete filling of it.
	void *tmp2;
	(void)tmp2;	
	void *array3[128];
	for (int i = 0; i < 128; i++)
	{
		array3[i] = ft_malloc(128);
		if (i == 0)
			tmp2 = array3[i];
		ft_memset(array3[i], 'C', 128);
	}
	
	// Printing the first and last five lines of each TINY heap.
	ft_hex_dump(g_heaps[TINY_HEAP], 512, 64);
	ft_printf("---\n");	
	ft_hex_dump(g_heaps[TINY_HEAP] + 20480 - 512, 512, 64);
	ft_printf("\n");
	ft_hex_dump(tmp1 - 16, 512, 64);
	ft_printf("---\n");	
	ft_hex_dump(tmp1 - 16 + 20480 - 512, 512, 64);
	ft_printf("\n");	
	ft_hex_dump(tmp2 - 16, 512, 64);
	ft_printf("---\n");	
	ft_hex_dump(tmp2 - 16 + 20480 - 512, 512, 64);
	//show_alloc_mem();
	
	// Freeing all the blocks except the last one of each heap.
	for (int i = 0; i < 127; i++)
		ft_free(array[i]);
	for (int i = 0; i < 127; i++)
		ft_free(array2[i]);
	for (int i = 0; i < 127; i++)
		ft_free(array3[i]);
	show_alloc_mem();
	
	// Printing the first address of each heap for reference.
	printf("First heap: \t\t\t%p\n", g_heaps[TINY_HEAP]);
	printf("Second heap: \t\t\t%p\n", tmp1-16);
	printf("Third heap: \t\t\t%p\n", tmp2-16);
	
	// Freeing the last block of each heap.	
	printf("Freeing last block third heap\n");
	ft_free(array[127]);
	printf("Freeing last block first heap\n");
	ft_free(array2[127]);
	printf("Freeing last block second heap\n");
	ft_free(array3[127]);

	show_alloc_mem();
		
	return (0);
}

// make && ./allocator | grep "128 bytes" | wc -l -> should return 384
// make && valgrind --leak-check=full ./allocator
// make && strace ./allocator 2>&1 | grep mmap
// make && /usr/bin/time -v ./allocator 0.00
