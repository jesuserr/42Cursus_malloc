/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 22:45:36 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/18 22:59:14 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// Goes across all the blocks in the given heap and returns false when finds
// the first allocated block. If all blocks are free, returns true.
// Only suitable for TINY and SMALL heaps.
t_bool	is_heap_empty(t_block *block)
{
	int		i;

	i = 0;
	while (i < PREALLOC_BLOCKS)
	{
		if (block->size & 0x1)
			return (false);
		block = block->next->next;
		i++;
	}
	return (true);
}

// Preallocates memory for TINY or SMALL heaps according to project subject.
// Populates only the first block to just trigger one minor page fault.
// The LSB of first size indicates if the block is allocated or free.
// Second size will be used to store the position of the block inside the heap.
// Returning a sentinel value like (void *)1 is a common practice to indicate
// success in functions that return pointers.
void	*init_tiny_or_small_heap(int heap_type, size_t heap_size)
{
	t_block	*block;

	g_heaps[heap_type] = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, \
		MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (g_heaps[heap_type] == MAP_FAILED)
		return (NULL);
	block = ((t_block *)g_heaps[heap_type]);
	if (heap_type == TINY_HEAP)
		block->size = TINY_BLOCK_SIZE;
	else
		block->size = SMALL_BLOCK_SIZE;
	block->next = NULL;
	return ((void *)1);
}

// Allocates a new heap (TINY or SMALL) with mmap populating only the first
// block in order to minimize minor page faults. New heap is attached at the end
// of current linked list of blocks. Returns the address of the first block
// payload of the new set (marked as allocated) for the user to use.
// The use of (unsigned char*) cast is to perform pointer arithmetic in a way 
// that ensures the arithmetic is done in terms of bytes.
void	*add_tiny_or_small_heap(int heap_type, size_t mem_req, t_block *block)
{
	void	*new_heap;
	t_block	*new_block;
	int		block_size;

	block_size = SMALL_BLOCK_SIZE;
	if (heap_type == TINY_HEAP)
	{
		block_size = TINY_BLOCK_SIZE;
		new_heap = mmap(NULL, TINY_HEAP_SIZE, PROT_READ | PROT_WRITE, \
		MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	}
	else
		new_heap = mmap(NULL, SMALL_HEAP_SIZE, PROT_READ | PROT_WRITE, \
		MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (new_heap == MAP_FAILED)
		return (NULL);
	new_block = (t_block *)new_heap;
	new_block->size = mem_req | 1;
	new_block->next = (t_block *)((unsigned char *)new_block + sizeof(t_block) \
		+ block_size);
	new_block->next->size = 1;
	new_block->next->next = new_block->next + 1;
	block->next->next = new_heap;
	write_log_to_file(" -> No free block found - New heap mapped", 0, NULL);
	return (new_block + 1);
}

// In some literature it is said that mmap rounds up 'size' to the next multiple
// of the system page size, just in case, it is done explicitly.
// Remember that received size is the requested user size + bytes needed for
// memory alignment.
void	*init_large_heap(size_t size)
{
	t_block	*block;
	size_t	mmap_size;

	mmap_size = size + BLOCK_OVERHEAD;
	mmap_size = (mmap_size + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
	g_heaps[LARGE_HEAP] = mmap(NULL, mmap_size, PROT_READ | PROT_WRITE, \
		MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (g_heaps[LARGE_HEAP] == MAP_FAILED)
		return (NULL);
	block = (t_block *)g_heaps[LARGE_HEAP];
	block->size = size | 1;
	block->next = (t_block *)((unsigned char *)block + sizeof(t_block) + \
		size);
	block->next->size = END_OF_HEAP_MARKER;
	block->next->next = (t_block *)END_OF_HEAP_PTR;
	return (block + 1);
}
