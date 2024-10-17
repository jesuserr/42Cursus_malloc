/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:13:44 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/17 16:59:41 by jesuserr         ###   ########.fr       */
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
		ft_printf("Borrado correcto\n");
	else
		ft_printf("ERROR Borrado incorrecto\n");
}

// Extracts the empty heap from the linked list of heaps and munmap it.
// The previous heap is updated to point to the next heap in the list.
// Basically it works with similar logic as 'free_large_heap'.
static void	free_tiny_small_heap(void *prev_heap, void *current_heap, \
		void *next_heap, int heap_type)
{
	t_block	*block;
	int		i;
	int		munmap_result;

	if (!prev_heap && next_heap == END_OF_HEAP_PTR)
		g_heaps[heap_type] = NULL;
	else if (!prev_heap && next_heap != END_OF_HEAP_PTR)
		g_heaps[heap_type] = next_heap;
	else
	{
		block = (t_block *)prev_heap;
		i = 0;
		while (i++ < PREALLOC_BLOCKS - 1)
			block = block->next->next;
		block->next->next = next_heap;
	}
	if (heap_type == TINY_HEAP)
		munmap_result = munmap(current_heap, TINY_HEAP_SIZE);
	else
		munmap_result = munmap(current_heap, SMALL_HEAP_SIZE);
	if (munmap_result == 0)
		ft_printf("Borrado correcto\n");
	else
		ft_printf("ERROR Borrado incorrecto\n");
}

// Verifies if the freeing of the block would leave an empty heap. If a heap is
// empty, it is freed with munmap calling 'free_tiny_small_heap'. Checks all the
// allocated heaps in the linked list. First heap will never be freed to avoid
// minor page faults being triggered. Only used for TINY and SMALL heaps.
static void	check_heap_if_empty(int heap_type, unsigned int heap_size)
{
	void		*prev_heap;
	void		*current_heap;
	void		*next_heap;
	void		*start;

	prev_heap = NULL;
	current_heap = g_heaps[heap_type];
	start = g_heaps[heap_type];
	next_heap = *(void **)(current_heap + heap_size - (sizeof(t_block) / 2));
	while (next_heap)
	{
		if (is_heap_empty((t_block *)current_heap) && current_heap != start)
			return (free_tiny_small_heap(prev_heap, current_heap, next_heap, \
				heap_type));
		if (next_heap == END_OF_HEAP_PTR)
			break ;
		prev_heap = current_heap;
		current_heap = next_heap;
		next_heap = *(void **)(next_heap + heap_size - (sizeof(t_block) / 2));
	}
}

// Checks if the block is really allocated and then proceeds to free it by
// setting block size to its default size, in addition, if all the blocks on a
// heap have been removed then the entire heap is freed with munmap (except for
// the first heap), for TINY / SMALL heaps only.
// For LARGE blocks, 'free_large_heap' is called to munmap and remove the block
// from the linked list of LARGE blocks.
static void	free_block_if_allocated(t_block *block, int heap_type)
{
	ft_printf("Block found %p on heap: %d\n", block, heap_type);
	if (block->size & 0x1)
	{
		if (heap_type == TINY_HEAP)
		{
			block->size = TINY_BLOCK_SIZE;
			check_heap_if_empty(heap_type, TINY_HEAP_SIZE);
		}
		else if (heap_type == SMALL_HEAP)
		{
			block->size = SMALL_BLOCK_SIZE;
			check_heap_if_empty(heap_type, SMALL_HEAP_SIZE);
		}
		else
			free_large_heap(block);
	}
	pthread_mutex_unlock(&g_mutex);
}

// Searches all existing heaps for the block to be freed. If the block is found,
// and it is allocated, it will be freed. If the block is not found, do/return
// nothing. Heaps are read from LARGE to TINY.
void	free(void *ptr)
{
	t_block	*block;
	int		heaps_to_read;

	if (!ptr)
		return ;
	pthread_mutex_lock(&g_mutex);
	heaps_to_read = LARGE_HEAP;
	while (heaps_to_read >= 0)
	{
		if (g_heaps[heaps_to_read])
		{
			block = (t_block *)g_heaps[heaps_to_read];
			while (block + 1 != ptr && block->next->next != END_OF_HEAP_PTR)
				block = block->next->next;
			if (block + 1 == ptr)
				return (free_block_if_allocated(block, heaps_to_read));
		}
		heaps_to_read--;
	}
	ft_printf("Block not found %p\n", block);
	pthread_mutex_unlock(&g_mutex);
}
