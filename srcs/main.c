/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:33:16 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/04 17:56:31 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int	main(void)
{
	ft_malloc(1);
	printf("%p\n", g_heaps[TINY_HEAP]);
	printf("%p\n", g_heaps[SMALL_HEAP]);
	printf("%p\n", g_heaps[LARGE_HEAP]);
	//ft_memset(g_heaps[TINY_HEAP], 'A', 20480);
	//ft_memset(g_heaps[SMALL_HEAP], 'B', 135168);
	ft_hex_dump(g_heaps[TINY_HEAP], 512, 32);
	printf("\n");
	ft_hex_dump(g_heaps[TINY_HEAP] + 20480 - 512, 512, 32);
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
