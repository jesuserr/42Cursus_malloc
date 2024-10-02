/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:33:16 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/02 21:43:26 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	main(void)
{
	ft_malloc(0);
	printf("%p\n", g_heaps[TINY_HEAP]);
	printf("%p\n", g_heaps[SMALL_HEAP]);
	printf("%p\n", g_heaps[LARGE_HEAP]);
	//ft_memset(g_heaps[TINY_HEAP], 'A', 20480);
	//ft_memset(g_heaps[SMALL_HEAP], 'B', 135168);
	hex_dump(g_heaps[TINY_HEAP], 512);
	printf("\n");
	hex_dump(g_heaps[TINY_HEAP] + 20480 - 512, 512);
	//printf("\n");
	//hex_dump(g_heaps[SMALL_HEAP], 2048 + 128);
	//printf("\n");
	//hex_dump(g_heaps[SMALL_HEAP] + 135168 - 2048 - 128, 2048 + 128);	
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
//
// Aplicar mascaras a block->size para indicar allocated or free
// Al ultimo bloque le he puesto todo FFs al tuntun (pensar)
//
// gestion de errores
