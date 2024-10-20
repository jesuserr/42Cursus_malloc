/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_heap_extension_and_free.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:33:16 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/20 18:11:10 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/malloc.h"

int	main(void)
{
	// Simulation of adding two new heaps to full SMALL heap and freeing later.	

	// Creates a SMALL heap and completely fills it with 128 blocks of 128 bytes
	// to force the creation of a new one in the next allocation.
	void *array[1024];	
	for (int i = 0; i < 128; i++)
	{
		array[i] = malloc(1024);
		ft_memset(array[i], 'A', 1024);
	}	
	
	// An extension of the SMALL heap will be made and the previous process
	// repeated again.
	void *tmp1;
	(void)tmp1;
	void *array2[1024];
	for (int i = 0; i < 128; i++)
	{
		array2[i] = malloc(1024);
		if (i == 0)
			tmp1 = array2[i];
		ft_memset(array2[i], 'B', 1024);
	}
	
	// Another extension of the SMALL heap and another complete filling of it.
	void *tmp2;
	(void)tmp2;	
	void *array3[1024];
	for (int i = 0; i < 128; i++)
	{
		array3[i] = malloc(1024);
		if (i == 0)
			tmp2 = array3[i];
		ft_memset(array3[i], 'C', 1024);
	}
	
	// Printing the first and last five lines of each SMALL heap.
	ft_hex_dump(g_heaps[SMALL_HEAP], 512, 64);
	ft_printf("---\n");	
	ft_hex_dump(g_heaps[SMALL_HEAP] + 135168 - 512, 512, 64);
	ft_printf("\n");
	ft_hex_dump(tmp1 - 16, 512, 64);
	ft_printf("---\n");	
	ft_hex_dump(tmp1 - 16 + 135168 - 512, 512, 64);
	ft_printf("\n");	
	ft_hex_dump(tmp2 - 16, 512, 64);
	ft_printf("---\n");	
	ft_hex_dump(tmp2 - 16 + 135168 - 512, 512, 64);
	show_alloc_mem();	
	
	// Freeing all the blocks except the last one of each heap.
	for (int i = 0; i < 127; i++)
		free(array[i]);
	for (int i = 0; i < 127; i++)
		free(array2[i]);
	for (int i = 0; i < 127; i++)
		free(array3[i]);
	show_alloc_mem();
	
	// Printing the first address of each heap for reference.
	ft_printf("First heap: \t\t\t%p\n", g_heaps[SMALL_HEAP]);
	ft_printf("Second heap: \t\t\t%p\n", tmp1-16);
	ft_printf("Third heap: \t\t\t%p\n", tmp2-16);
	
	// Freeing the last block of each heap.
	ft_printf("Freeing last block third heap\n");
	free(array3[127]);	
	ft_printf("Freeing last block first heap\n");
	free(array[127]);
	ft_printf("Freeing last block second heap\n");
	free(array2[127]);	

	show_alloc_mem();
	
	return (0);
}

// gcc -o small_heap_extension_and_free small_heap_extension_and_free.c -L. -L../libft -lft_malloc -lft && ./run_linux.sh ./small_heap_extension_and_free