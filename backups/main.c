/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:33:16 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/02 16:12:12 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	main(void)
{
	char	*str;

	printf("System Page Size: %d\n", PAGE_SIZE);
	str = custom_malloc(getpagesize() / 128);
	if (!str)
		return (1);
	printf("Returned pointer: %p\n", str);
	ft_memset(str, 'A', getpagesize() / 128 + 0 );
	ft_memset(str, 'B', 1);
	ft_memset(str + getpagesize() / 128 - 1, 'B', 1);	
	printf("%d %d\n", TINY_BLOCK_SIZE, SMALL_BLOCK_SIZE);
	printf("%d %d\n", PAGE_SIZE, PREALLOC_BLOCKS);
	printf("%d \n", TINY_BLOCK_SIZE * PREALLOC_BLOCKS);
	printf("%d \n", SMALL_BLOCK_SIZE * PREALLOC_BLOCKS);
	hex_dump(str, getpagesize() / 128);
	custom_free(str);
		
	ft_malloc(128);	
	printf("%p\n", g_heaps[TINY_HEAP]);
	printf("%p\n", g_heaps[SMALL_HEAP]);
	printf("%p\n", g_heaps[LARGE_HEAP]);
	ft_malloc(128);	
	printf("%p\n", g_heaps[TINY_HEAP]);
	printf("%p\n", g_heaps[SMALL_HEAP]);
	printf("%p\n", g_heaps[LARGE_HEAP]);
	ft_malloc(128);	
	printf("%p\n", g_heaps[TINY_HEAP]);
	printf("%p\n", g_heaps[SMALL_HEAP]);
	printf("%p\n", g_heaps[LARGE_HEAP]);
	
	char *str2 = malloc(0);
	printf("Returned pointer: %p\n", str2);
	char *str3 = ft_malloc(0);
	printf("Returned pointer: %p\n", str3);
	
	

	return (0);
}

// make && valgrind --leak-check=full ./allocator
// make && strace ./allocator 2>&1 | grep mmap
// make && /usr/bin/time -v ./allocator 0.00
// NOTES
// my printf is not ready to print size_t
// 
// malloc - SUSv3 specifies that the call malloc(0) may return either NULL or
// a pointer to a small piece of memory that can (and should) be freed with
// free(). On Linux, malloc(0) follows the latter behavior.