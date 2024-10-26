/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:13:44 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/26 20:31:58 by jesuserr         ###   ########.fr       */
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
static void	free_large_heap(t_block *block)
{
	t_block	*prev_block;
	size_t	munmap_size;

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
	munmap_size = (block->size);
	munmap_size = (munmap_size + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
	if (munmap(block, munmap_size) == 0)
		write_log_to_file(" -> LARGE heap unmapped successfully", 0, NULL);
	else
		write_log_to_file(" -> Error unmapping LARGE heap", 0, NULL);
}

// Searches for the block to be freed. If block is found, 'free_large_heap' is
// called to munmap and remove the block from the linked list of LARGE blocks.
// If it is not found nothing is done.
void	free(void *ptr)
{
	t_block	*block;

	if (!ptr)
		return ;
	pthread_mutex_lock(&g_mutex);
	if (g_heaps[LARGE_HEAP])
	{
		block = (t_block *)g_heaps[LARGE_HEAP];
		while (block + 1 != ptr && block->next->next != END_OF_HEAP_PTR)
			block = block->next->next;
		if (block + 1 == ptr)
		{
			write_log_to_file("Released:", block->size, block + 1);
			free_large_heap(block);
		}
		else
			write_log_to_file("\nFree error: Pointer not found", 0, NULL);
	}
	pthread_mutex_unlock(&g_mutex);
}
