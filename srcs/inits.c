/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 22:45:36 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/11 22:50:59 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// Format preallocated heaps using linked list of blocks that use boundary tags.
// Applicable only to TINY and SMALL heaps. The use of (unsigned char*) cast is
// to perform pointer arithmetic in a way that ensures the arithmetic is done in
// terms of bytes. The LSB of size indicates if the block is allocated or free.
void	heaps_formatting(size_t block_size, void *heap)
{
	t_block	*block;
	int		i;

	block = (t_block *)heap;
	i = 0;
	while (i < PREALLOC_BLOCKS)
	{
		block->size = block_size;
		block->next = (t_block *)((unsigned char *)block + sizeof(t_block) + \
			block_size);
		block = block->next;
		if (i < PREALLOC_BLOCKS - 1)
		{
			block->size = block_size;
			block->next = block + 1;
			block = block->next;
		}
		else
		{
			block->size = END_OF_HEAP_MARKER;
			block->next = (t_block *)END_OF_HEAP_PTR;
		}
		i++;
	}
}

// Preallocates memory maps for TINY and SMALL heaps according to project 
// subject and formats them as linked lists of blocks that use boundary tags.
// Returning a sentinel value like (void *)1 is a common practice to indicate
// success in functions that return pointers.
void	*init_tiny_and_small_heaps(int heap_type)
{
	if (heap_type == TINY_HEAP)
	{
		g_heaps[TINY_HEAP] = mmap(NULL, TINY_HEAP_SIZE, PROT_READ | PROT_WRITE, \
			MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
		if (g_heaps[TINY_HEAP] == MAP_FAILED)
			return (NULL);
		heaps_formatting(TINY_BLOCK_SIZE, g_heaps[TINY_HEAP]);
	}
	else if (heap_type == SMALL_HEAP)
	{
		g_heaps[SMALL_HEAP] = mmap(NULL, SMALL_HEAP_SIZE, PROT_READ | \
			PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
		if (g_heaps[SMALL_HEAP] == MAP_FAILED)
			return (NULL);
		heaps_formatting(SMALL_BLOCK_SIZE, g_heaps[SMALL_HEAP]);
	}
	return ((void *)1);
}

// Allocates a new heap (TINY or SMALL) with mmap and formats it as a linked
// list of blocks that use boundary tags. New heap is attached to the current
// linked list of blocks. Returns the address of the first block of the new set
// (marked as allocated) for the user to use.
void	*add_tiny_or_small_heap(int heap_type, size_t mem_req, t_block *block)
{
	unsigned int	real_size;
	void			*new_heap;
	t_block			*new_block;

	if (heap_type == TINY_HEAP)
		real_size = TINY_HEAP_SIZE;
	else
		real_size = SMALL_HEAP_SIZE;
	new_heap = mmap(NULL, real_size, PROT_READ | PROT_WRITE, \
		MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (new_heap == MAP_FAILED)
		return (NULL);
	if (heap_type == TINY_HEAP)
		heaps_formatting(TINY_BLOCK_SIZE, new_heap);
	else
		heaps_formatting(SMALL_BLOCK_SIZE, new_heap);
	new_block = (t_block *)new_heap;
	new_block->size = mem_req | 1;
	new_block->next->size = mem_req | 1;
	block->next->size = block->size;
	block->next->next = new_heap;
	ft_printf("New heap added\n");
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
