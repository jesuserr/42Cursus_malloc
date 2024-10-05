/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:12:45 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/05 13:43:59 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// Global variables are automatically initialized to zero if they are not
// explicitly initialized.
void	*g_heaps[3];

// So far returns NULL if no free block is found, modify to expand heap
void	*search_free_block(enum e_heap_type heap_type, size_t mem_req)
{
	t_block	*block;
	size_t	mem_available;
	t_bool	block_allocated;

	block = (t_block *)g_heaps[heap_type];
	while (block->size != END_OF_HEAP_MARKER)
	{
		mem_available = block->size & ~0x1;
		block_allocated = block->size & 0x1;
		if (mem_available >= mem_req && !block_allocated)
		{
			block->size = mem_req | 1;
			if (block->next->size != END_OF_HEAP_MARKER)
				block->next->size = mem_req | 1;
			return (++block);
		}
		if (block->next->size == END_OF_HEAP_MARKER)
			break ;
		block = block->next->next;
	}
	printf("No free block found\n");
	return (NULL);
}

// Follows SUSv3 specification that malloc(0) may return NULL
// ** returning sentinel value, modify it later with real pointer **
// size = ((size + 7) >> 3) << 3; // Round up to the nearest multiple of 8	
void	*ft_malloc(size_t size)
{
	if (size == 0)
		return (NULL);
	if (!g_heaps[TINY_HEAP] && !g_heaps[SMALL_HEAP])
		if (!init_heaps())
			return (NULL);
	size = ((size + 7) >> 3) << 3;
	if (size <= TINY_BLOCK_SIZE)
		return (search_free_block(TINY_HEAP, size));
	else if (size <= SMALL_BLOCK_SIZE)
		return (search_free_block(SMALL_HEAP, size));
	else
		printf("Goes to LARGE\n");
	return ((void *)1);
}
