/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:13:44 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/12 13:17:29 by jesuserr         ###   ########.fr       */
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

// Extracts the empty heap from the linked list of heaps and munmap it.
// The previous heap is updated to point to the next heap in the list.
// *(void **)heap, allows to obtain the pointer contained in the pointer 'heap'.
void	free_tiny_small_heap(void *prev_heap, void *c_heap, void *n_heap, unsigned int heapsize, int heap_type)
{
	t_block	*block;
	int		i;
	int		munmap_result;
	void	*next_heap;
	(void)heapsize;
	(void)munmap_result;
	(void)prev_heap;
	
	next_heap = *(void **)n_heap;
	printf("Previous heap address: \t\t%p\n", prev_heap);
	printf("Current heap address: \t\t%p\n", c_heap);
	printf("Next heap address: \t\t%p\n", next_heap);
	
	if (c_heap == g_heaps[heap_type] && next_heap == END_OF_HEAP_PTR)
	{
		printf("Only heap!!\n");
		g_heaps[heap_type] = NULL;
	}
	else if (c_heap == g_heaps[heap_type] && next_heap != END_OF_HEAP_PTR)
	{
		printf("First heap!!\n");
		g_heaps[heap_type] = next_heap;
	}
	else
	{
		block = (t_block *)c_heap;
		i = 0;
		while (i++ < PREALLOC_BLOCKS - 1)
			block = block->next->next;
		block->next->next = next_heap;
	}
	//next_heap = *(void **)(current_heap + heapsize - (sizeof(t_block) / 2));
	munmap_result = munmap(c_heap, heapsize);
	if (munmap_result == 0)
		printf("Borrado correcto\n");
	else
		perror("munmap");
}
//printf("Previous heap is \t\t%p\n", prev_heap);
//printf("Block's heap starting at \t%p\n", current_heap);
//printf("Next heap address: \t\t%p\n", next_heap);

// Verifies if the freeing of the block would leave an empty heap. If a heap is
// empty, it is freed with munmap calling 'free_tiny_small_heap'. Checks all the
// allocated heaps in the linked list.
void	old_check_heap_if_empty(int heap_type, unsigned int heap_size)
{
	void			*prev_heap;
	void			*current_heap;
	void			*next_heap;	
	t_block			*block;
	int				i;

	prev_heap = NULL;
	current_heap = g_heaps[heap_type];
	next_heap = g_heaps[heap_type] + heap_size - (sizeof(t_block) / 2);
	while (*(void **)next_heap != END_OF_HEAP_PTR)
	{
		block = (t_block *)current_heap;
		i = 0;
		while (i < PREALLOC_BLOCKS)
		{
			if (block->size & 0x1)
				break ;
			block = block->next->next;
			i++;
		}
		if (i == PREALLOC_BLOCKS)
			return (free_tiny_small_heap(prev_heap, current_heap, next_heap, heap_size, heap_type));
		prev_heap = current_heap;
		current_heap = *(void **)next_heap;
		next_heap = *(void **)next_heap + heap_size - (sizeof(t_block) / 2);
	}
}

// Verifies if the freeing of the block would leave an empty heap. If a heap is
// empty, it is freed with munmap calling 'free_tiny_small_heap'. Checks all the
// allocated heaps in the linked list.
void	check_heap_if_empty(int heap_type, unsigned int heap_size)
{
	void		*current_heap;
	void		*next_heap;
	t_block		*block;
	int			i;	
	
	current_heap = g_heaps[heap_type];
	next_heap = g_heaps[heap_type] + heap_size - (sizeof(t_block) / 2);
	next_heap = *(void **)next_heap;	
	while (1)
	{
		printf("Heap address: %p\n", current_heap);
		printf("Next heap address: %p\n", next_heap);
		block = (t_block *)current_heap;
		i = 0;
		while (i < PREALLOC_BLOCKS)
		{
			if (block->size & 0x1)
				break ;
			block = block->next->next;
			i++;
		}
		if (i == PREALLOC_BLOCKS)
		{
			printf("Heap is empty\n");
			return ;
		}
		if (next_heap == END_OF_HEAP_PTR)
			break;
		current_heap =  next_heap;
		printf("updated current heap: %p\n", current_heap);
		next_heap = *(void**)(next_heap + heap_size - (sizeof(t_block) / 2));		
		printf("updated next heap: %p\n", next_heap);
	}
	printf("Nothing empty\n");
}

// Checks if the block is really allocated and then proceeds to free it by
// setting block size to its default size, in addition, if all the blocks on a
// heap have been removed the entire heap is freed with munmap
// (for TINY / SMALL heaps only). For LARGE blocks, 'free_large_heap' is called
// to munmap and remove the block from the linked list of LARGE blocks.
void	free_block_if_allocated(t_block *block, int heap_type)
{
	printf("Block found %p on heap: %d\n", block, heap_type);
	if (block->size & 0x1)
	{
		if (heap_type == TINY_HEAP)
		{
			block->size = TINY_BLOCK_SIZE;
			block->next->size = TINY_BLOCK_SIZE;
			check_heap_if_empty(heap_type, TINY_HEAP_SIZE);
		}
		else if (heap_type == SMALL_HEAP)
		{
			block->size = SMALL_BLOCK_SIZE;
			block->next->size = SMALL_BLOCK_SIZE;
			check_heap_if_empty(heap_type, SMALL_HEAP_SIZE);
		}
		else
			free_large_heap(block);
	}
}

// Searches all existing heaps for the block to be freed. If the block is found,
// and it is allocated, it will be freed. If the block is not found, do/return
// nothing. Heaps are read from LARGE to TINY.
void	ft_free(void *ptr)
{
	t_block	*block;
	int		heaps_to_read;

	if (!ptr)
		return ;
	heaps_to_read = 3;
	while (heaps_to_read > 0)
	{
		if (g_heaps[heaps_to_read - 1])
		{
			block = (t_block *)g_heaps[heaps_to_read - 1];
			while (block + 1 != ptr && block->next->next != END_OF_HEAP_PTR)
				block = block->next->next;
			if (block + 1 == ptr)
				return (free_block_if_allocated(block, heaps_to_read - 1));
		}
		heaps_to_read--;
	}
	printf("Block not found %p\n", block);
}
