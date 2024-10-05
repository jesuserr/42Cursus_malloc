/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:13:44 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/05 21:36:46 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// The free() function frees the memory space pointed to by ptr, which must have
// been returned by a previous call to malloc(), calloc(), or realloc().
// Otherwise, or if free(ptr) has already been called before, undefined behavior
// occurs. If ptr is NULL, no operation is performed. The free() function
// returns no value.

// Checks if the block is really allocated and then proceeds to free it to its
// default size. So far only TINY and SMALL heaps are handled.
void	free_block_if_allocated(t_block *block, int i)
{
	if (block->size & 0x1)
	{
		if (i == TINY_HEAP)
		{
			block->size = TINY_BLOCK_SIZE;
			block->next->size = TINY_BLOCK_SIZE;
		}
		else if (i == SMALL_HEAP)
		{
			block->size = SMALL_BLOCK_SIZE;
			block->next->size = SMALL_BLOCK_SIZE;
		}
	}
}

// TODO: Implemented without splitting blocks and without coalescing adjacent
// TODO: LARGE heap blocks, now searches only TINY and SMALL heaps
// TODO: munmap to release memory back to the system
// If the LARGE_HEAP has not been initialized, only TINY and SMALL heaps are
// searched for the block to be freed. If the block is found, it will be freed
// if it is allocated. If the block is not found, do/return nothing.
// Heaps are read from LARGE to TINY.
void	ft_free(void *ptr)
{
	t_block	*block;
	int		heaps_to_read;

	if (!ptr)
		return ;
	heaps_to_read = 2;
	if (g_heaps[LARGE_HEAP])
		heaps_to_read = 3;
	while (heaps_to_read > 0)
	{
		block = (t_block *)g_heaps[heaps_to_read - 1];
		while (block + 1 != ptr && block->next->size != END_OF_HEAP_MARKER)
			block = block->next->next;
		if (block + 1 == ptr)
			return (free_block_if_allocated(block, heaps_to_read - 1));
		heaps_to_read--;
	}
	printf("Block not found %p\n", block);
}
