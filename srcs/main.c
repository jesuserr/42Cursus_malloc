/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:33:16 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/08 23:29:51 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int	main(void)
{
	printf("Memory Alignment: %ld bytes\n", MEMORY_ALIGNMENT);
	printf("Tiny Size: %ld\n", (TINY_BLOCK_SIZE + BLOCK_OVERHEAD) * PREALLOC_BLOCKS);
	printf("Small Size: %ld\n", (SMALL_BLOCK_SIZE + BLOCK_OVERHEAD) * PREALLOC_BLOCKS);		
	
	printf("Large Size: %p\n", g_heaps[LARGE_HEAP]);
	
	void *ptr22 = ft_malloc(1040);	
	ft_memset(ptr22, 'A', 1040);	
	ft_hex_dump(ptr22 - 16, 1040 + 16, 64);
	printf("\n");
	
	void *ptr23 = ft_malloc(2048);
	ft_memset(ptr23, 'B', 2048);
	ft_hex_dump(ptr23 - 16, 2048 + 16, 64);
	printf("\n");	
	
	void *ptr24 = ft_malloc(3088);	
	ft_memset(ptr24, 'C', 3088);
	ft_hex_dump(ptr24 - 16, 3088 + 16, 64);
	printf("\n");	
	
	//system("clear");
	printf("Large Size: %p\n", g_heaps[LARGE_HEAP]);
	printf("%p\n", ptr22);
	printf("%p\n", ptr23);
	printf("%p\n", ptr24);
	
	ft_free(ptr23);
	ft_free(ptr22);
	//ft_free(ptr24);
	//ft_hex_dump(ptr22 - 16, 1040 + 16, 64);
	printf("\n");
	//ft_hex_dump(ptr23 - 16, 2048 + 16, 64);
	printf("\n");	
	ft_hex_dump(ptr24 - 16, 3088 + 64, 64);
	printf("\n");
	
	printf("Large Size: %p\n", g_heaps[LARGE_HEAP]);
	
	/*
	system("clear");
	
	void *ptr113 = ft_malloc(13);
	void *ptr114 = ft_malloc(13);	
	ft_memset(ptr113, 'X', 13);
	ft_memset(ptr114, 'Y', 13);
	printf("\n");
	ft_hex_dump(g_heaps[TINY_HEAP], 1024, 64);
	printf("\n");
	ft_free(ptr114);
	printf("\n");
	ft_hex_dump(g_heaps[TINY_HEAP], 1024, 64);
	*/
	
	

	

	/*

	ft_hex_dump(g_heaps[LARGE_HEAP], 1025, 64);
	printf("\n");
	ft_memset(ptr22, 'A', 1025);	
	ft_hex_dump(g_heaps[LARGE_HEAP], 1025, 64);	
	printf("\n");
	//ft_free(ptr22);
	//printf("Large Size: %p\n", g_heaps[LARGE_HEAP]);
	void *ptr23 = ft_malloc(1025);
	if (ptr23 == NULL)
		printf("Malloc failed\n");
	ft_hex_dump(g_heaps[LARGE_HEAP], 6025, 64);	*/
	return (0);	

	void *ptr = ft_malloc(31);
	if (ptr == NULL)
		printf("Malloc failed\n");
	ft_memset(ptr, 'A', 31);
	
	void *ptr2 = ft_malloc(32);
	if (ptr2 == NULL)
		printf("Malloc failed\n");
	ft_memset(ptr2, 'B', 32);
	
	void *ptr3 = ft_malloc(133);
	if (ptr3 == NULL)
		printf("Malloc failed\n");
	ft_memset(ptr3, 'C', 133);

	printf("\n");
	ft_hex_dump(g_heaps[TINY_HEAP], 512, 64);
	printf("\n");
	ft_hex_dump(g_heaps[SMALL_HEAP], 1024 + 16, 64);		
	
	ft_free(ptr);
	ft_free(ptr2);
	ft_free(ptr3);
	
	printf("\n");
	ft_hex_dump(g_heaps[TINY_HEAP], 512, 64);
	printf("\n");
	ft_hex_dump(g_heaps[SMALL_HEAP], 1024 + 16, 64);
		
	void *ptr4 = ft_malloc(1024);
	if (ptr4 == NULL)
		printf("Malloc failed\n");
	ft_memset(ptr4, 'X', 1024);	
	printf("\n");
	ft_hex_dump(g_heaps[TINY_HEAP], 512, 64);
	printf("\n");
	ft_hex_dump(g_heaps[SMALL_HEAP], 1024 + 16, 64);
	printf("\n");
	return (0);	
}

// make && valgrind --leak-check=full ./allocator
// make && strace ./allocator 2>&1 | grep mmap
// make && /usr/bin/time -v ./allocator 0.00
// NOTES
// my printf is not ready to print size_t
// 
// gestion de errores
//
// 9223372036854775807 (biggest number that can be put in real malloc)
//
// git submodule update --remote libft
