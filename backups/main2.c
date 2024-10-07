/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:33:16 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/06 19:51:12 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int	main(void)
{
	printf("Memory Alignment: %ld bytes\n", MEMORY_ALIGNMENT);
	printf("Tiny Size: %ld\n", (TINY_BLOCK_SIZE + BLOCK_OVERHEAD) * PREALLOC_BLOCKS);
	printf("Small Size: %ld\n", (SMALL_BLOCK_SIZE + BLOCK_OVERHEAD) * PREALLOC_BLOCKS);

	void *ptr = ft_malloc(16);
	if (ptr == NULL)
		printf("Malloc failed\n");
	ft_memset(ptr, 'A', 16);
	
	void *ptr2 = ft_malloc(32);
	if (ptr2 == NULL)
		printf("Malloc failed\n");
	ft_memset(ptr2, 'B', 32);
	
	void *ptr3 = ft_malloc(64);
	if (ptr3 == NULL)
		printf("Malloc failed\n");
	ft_memset(ptr3, 'C', 64);

	ft_hex_dump(g_heaps[TINY_HEAP], 512 + 64, 64);
	printf("\n");
	//ft_hex_dump(g_heaps[TINY_HEAP] + 20480 - 512, 512, 64);
	printf("\n");
	
	ft_free(ptr);
	
	ft_hex_dump(g_heaps[TINY_HEAP], 512 + 64, 64);
	printf("\n");
	//ft_hex_dump(g_heaps[TINY_HEAP] + 20480 - 512, 512, 64);
	printf("\n");
		
	void *ptr4 = ft_malloc(48);
	if (ptr4 == NULL)
		printf("Malloc failed\n");
	ft_memset(ptr4, 'X', 48);
	
	ft_hex_dump(g_heaps[TINY_HEAP], 512 + 64, 64);
	printf("\n");
	
	//ft_hex_dump(g_heaps[TINY_HEAP] + 20480 - 512, 512, 64);
	
	void *ptr5 = ft_malloc(148);
	if (ptr5 == NULL)
		printf("Malloc failed\n");
	ft_memset(ptr5, 'E', 148);
	ft_hex_dump(g_heaps[SMALL_HEAP], 1024 + 48, 64);
	printf("\n");
	ft_free(ptr5);
	ft_hex_dump(g_heaps[SMALL_HEAP], 1024 + 48, 64);
	
	void *array[100];
	for (int i = 0; i < 100; i++)
	{
		array[i] = malloc(4095);
		printf("%d", (4095 + 16 - 1) & ~(4095 - 1));
		printf("Array[%d]: %p\n", i, array[i]);		
	}
	
	int i = 1024;
	void* ptr6 = malloc(i);	
	void* ptr7 = malloc(i);
	printf("Ptr6: %p\n", ptr6);
	printf("Ptr7: %p\n", ptr7);
	printf("Ptr7 - Ptr6: %ld\n", ptr7 - ptr6);
	printf("%d\n", ((i + 16 - 1) & ~(16 - 1)));
	
	
	
	//ft_hex_dump(g_heaps[TINY_HEAP], 512, 64);
	//printf("\n");
	//ft_hex_dump(g_heaps[TINY_HEAP] + 20480 - 512, 512, 64);

	//ft_memset(g_heaps[SMALL_HEAP], 'B', 135168);
	
	//printf("\n");
	//ft_hex_dump(g_heaps[TINY_HEAP] + 20480 - 512, 512, 16);
	//printf("\n");
	//ft_hex_dump(g_heaps[SMALL_HEAP], 2048 + 128, 64);
	//printf("\n");
	//ft_hex_dump(g_heaps[SMALL_HEAP] + 135168 - 2048, 2048, 64);
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
