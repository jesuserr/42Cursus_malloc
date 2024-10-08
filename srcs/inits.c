/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 22:45:36 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/08 23:56:31 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// Returning a sentinel value like (void *)1 is a common practice to indicate
// success in functions that return pointers.
void	*heaps_preallocation(void)
{
	unsigned int	real_tiny_size;
	unsigned int	real_small_size;

	real_tiny_size = (TINY_BLOCK_SIZE + BLOCK_OVERHEAD) * PREALLOC_BLOCKS;
	real_small_size = (SMALL_BLOCK_SIZE + BLOCK_OVERHEAD) * PREALLOC_BLOCKS;
	g_heaps[TINY_HEAP] = mmap(NULL, real_tiny_size, PROT_READ | PROT_WRITE, \
		MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (g_heaps[TINY_HEAP] == MAP_FAILED)
		return (NULL);
	g_heaps[SMALL_HEAP] = mmap(NULL, real_small_size, PROT_READ | PROT_WRITE, \
		MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (g_heaps[SMALL_HEAP] == MAP_FAILED)
	{
		munmap(g_heaps[TINY_HEAP], real_tiny_size);
		return (NULL);
	}
	return ((void *)1);
}

// Format preallocated heaps using linked list of blocks that use boundary tags
// Applicable only to TINY and SMALL heaps
// The use of unsigned char* in line 50 is to perform pointer arithmetic in
// a way that ensures the arithmetic is done in terms of bytes.
// The LSB of size indicates if the block is allocated or free
void	heaps_formatting(enum e_heap_type heap_type, size_t block_size)
{
	t_block	*block;
	int		i;

	block = (t_block *)g_heaps[heap_type];
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

// Returning a sentinel value like (void *)1 is a common practice to indicate
// success in functions that return pointers.
void	*init_tiny_and_small_heaps(void)
{
	if (!heaps_preallocation())
		return (NULL);
	heaps_formatting(TINY_HEAP, TINY_BLOCK_SIZE);
	heaps_formatting(SMALL_HEAP, SMALL_BLOCK_SIZE);
	return ((void *)1);
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
