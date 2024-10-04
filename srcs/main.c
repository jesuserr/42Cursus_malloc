/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:33:16 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/05 00:03:27 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int	main(void)
{
	void *ret;
	ret = ft_malloc(7);
	printf("Malloc: %p\n", ret);
	printf("Tiny: %p\n", g_heaps[TINY_HEAP]);
	printf("Small: %p\n", g_heaps[SMALL_HEAP]);
	printf("Large: %p\n", g_heaps[LARGE_HEAP]);
	
	//ft_memset(g_heaps[TINY_HEAP] + 16, 'A', 27);
	ft_memset(ret, 'A', 7);

	void *ret2;
	ret2 = ft_malloc(8);	
	ft_memset(ret2, 'B', 8);
	void *ret3;
	ret3 = ft_malloc(9);	
	ft_memset(ret3, 'C', 9);
	ft_hex_dump(ret - 16, 512, 16);
	//printf("\n");
	//ft_hex_dump(g_heaps[TINY_HEAP] + 20480 - 512, 512, 16);

	//ft_memset(g_heaps[SMALL_HEAP], 'B', 135168);
	
	//printf("\n");
	//ft_hex_dump(g_heaps[TINY_HEAP] + 20480 - 512, 512, 16);
	//printf("\n");
	//hex_dump(g_heaps[SMALL_HEAP], 2048 + 128, 64);
	//printf("\n");
	//hex_dump(g_heaps[SMALL_HEAP] + 135168 - 2048 - 128, 2048 + 128, 64);
	return (0);
}

// make && valgrind --leak-check=full ./allocator
// make && strace ./allocator 2>&1 | grep mmap
// make && /usr/bin/time -v ./allocator 0.00
// NOTES
// my printf is not ready to print size_t
// 
// Aplicar mascaras a block->size para indicar allocated or free
// Al ultimo bloque le he puesto todo FFs al tuntun (pensar)
//
// gestion de errores
//
// 9223372036854775807 (biggest number that can be put in real malloc)
