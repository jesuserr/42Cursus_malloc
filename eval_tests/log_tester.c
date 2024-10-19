/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_tester.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:33:16 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/19 13:54:17 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/malloc.h"

int	main(void)
{
	void *ptr1 = malloc(1);
	void *ptr2 = malloc(2);
	void *ptr4 = malloc(4);
	void *ptr8 = malloc(8);
	void *ptr16 = malloc(16);
	void *ptr32 = malloc(32);
	void *ptr64 = malloc(64);
	void *ptr128 = malloc(128);
	
	void *ptr256 = malloc(256);
	void *ptr512 = malloc(512);
	void *ptr1024 = malloc(1024);
	
	void *ptr2048 = malloc(2048);
	void *ptr4096 = malloc(4096);
	void *ptr8192 = malloc(8192);
	void *ptr16384 = malloc(16384);
	void *ptr32768 = malloc(32768);
	void *ptr65536 = malloc(65536);
	void *ptr131072 = malloc(131072);
	void *ptr262144 = malloc(262144);
	void *ptr524288 = malloc(524288);
	void *ptr1048576 = malloc(1048576);
		
	ft_memset(ptr1, 'A', 1);
	ft_memset(ptr2, 'B', 2);
	ft_memset(ptr4, 'C', 4);
	ft_memset(ptr8, 'D', 8);
	ft_memset(ptr16, 'E', 16);
	ft_memset(ptr32, 'F', 32);
	ft_memset(ptr64, 'G', 64);
	ft_memset(ptr128, 'H', 128);
	ft_memset(ptr256, 'I', 256);
	ft_memset(ptr512, 'J', 512);
	ft_memset(ptr1024, 'K', 1024);
	ft_memset(ptr2048, 'L', 2048);
	ft_memset(ptr4096, 'M', 4096);
	ft_memset(ptr8192, 'N', 8192);
	ft_memset(ptr16384, 'O', 16384);
	ft_memset(ptr32768, 'P', 32768);
	ft_memset(ptr65536, 'Q', 65536);
	ft_memset(ptr131072, 'R', 131072);
	ft_memset(ptr262144, 'S', 262144);
	ft_memset(ptr524288, 'T', 524288);
	ft_memset(ptr1048576, 'U', 1048576);
	
	// Simulation of free and re-malloc on TINY heap
	free(ptr32);
	ptr32 = malloc(32);
	
	// Simulation of free and re-malloc on SMALL heap
	free(ptr512);	
	ptr512 = malloc(512);
		
	// Simulation of free and re-malloc on LARGE heap
	free(ptr2048);
	ptr2048 = malloc(2048);
	
	// Simulation of realloc on LARGE heap, doubling the size
	ptr1048576 = realloc(ptr1048576, 1048576 * 2);
	
	// Simulation of calloc SMALL heap	
	void *ptrAAA;
	(void)ptrAAA;
	ptrAAA = calloc(1024, 1024);
	
	// Forcing two new TINY heaps to be created and free one
	void *array[256];
	for (int i = 0; i < 256; i++)
		array[i] = malloc(128);
	for (int i = 0; i < 256; i++)
		free(array[i]);

	// Forcing free errors (non allocated pointer and double free)
	free(ptr16);
	free(ptr16 - 32);
	free(ptr16);
	
	//show_alloc_mem();	
	return (0);
}

// gcc -o log_tester log_tester.c -L. -lft_malloc && ./run_linux.sh ./log_tester