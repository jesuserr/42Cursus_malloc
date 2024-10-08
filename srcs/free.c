/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:13:44 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/09 00:28:28 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// The free() function frees the memory space pointed to by ptr, which must have
// been returned by a previous call to malloc(), calloc(), or realloc().
// Otherwise, or if free(ptr) has already been called before, undefined behavior
// occurs. If ptr is NULL, no operation is performed. The free() function
// returns no value.

// In some literature it is said that munmap rounds up 'size' to the next
// multiple of the system page size, just in case, it is done explicitly.
// Given a block to be freed, the function locates the previous block in order
// to link it with the next block of the block to be freed (as long as the block
// is not the first one in the heap). If the block is the first and only, the
// heap is set to NULL, if the block is the first but not the only one, the head
// of the list is updated to the next block. The block is then munmapped.
void	free_large_heap(t_block *block)
{
	t_block	*prev_block;
	size_t	munmap_size;
	int		munmap_result;

	prev_block = (t_block *)g_heaps[LARGE_HEAP];
	if (prev_block == block && block->next->next == END_OF_HEAP_PTR)
		g_heaps[LARGE_HEAP] = NULL;
	else if (prev_block == block && block->next->next != END_OF_HEAP_PTR)
		g_heaps[LARGE_HEAP] = block->next->next;
	else
	{
		while (prev_block->next->next != block)
			prev_block = prev_block->next->next;
		prev_block->next->next = block->next->next;
	}
	munmap_size = (block->size & ~0x1);
	munmap_size = (munmap_size + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
	munmap_result = munmap(block, munmap_size);
	if (munmap_result == 0)
		printf("Borrado correcto\n");
	else
		perror("munmap");
}

// Checks if the block is really allocated and then proceeds to free it by
// setting the size of the block to its default size (for TINY / SMALL blocks).
// For LARGE blocks, free_large_heap is called to munmap and remove the block
// from the linked list of LARGE blocks.
void	free_block_if_allocated(t_block *block, int i)
{
	printf("Block found %p on heap: %d\n", block, i);
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
		else
			free_large_heap(block);
	}
}

// TODO: Implemented without splitting blocks and without coalescing adjacent
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
		while (block + 1 != ptr && block->next->next != END_OF_HEAP_PTR)
			block = block->next->next;
		if (block + 1 == ptr)
			return (free_block_if_allocated(block, heaps_to_read - 1));
		heaps_to_read--;
	}
	printf("Block not found %p\n", block);
}
