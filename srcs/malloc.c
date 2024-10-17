/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:12:45 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/17 16:58:52 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// The malloc() function allocates size bytes and returns a pointer to the
// allocated memory. The memory is not initialized. If size is 0, then 
// malloc() returns either NULL, or a unique pointer value that can later be
// successfully passed to free(). The malloc() function returns a pointer to the
// allocated memory, which is suitably aligned for any built-in type. On error
// this function return NULL. NULL may also be returned by a successful call
// to malloc() with a size of zero.

// Global variables are automatically initialized to zero if they are not
// explicitly initialized. Static init of the mutex with default attributes.
void			*g_heaps[3];
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

// Fills the block metadata and returns the address of the block payload.
// It takes into account if is the first time that the metadata is written on
// the block or not. The first time that a block is created is the last in the
// linked list and therefore the 'next->next' pointer is set to END_OF_HEAP_PTR.
// If this block is freed and allocated again, no metadata has to be changed
// except for the allocation bit, that is done outside this function.
static
t_block	*set_block_metadata(t_block *block, int block_size, size_t block_pos)
{
	if (!block->next)
	{
		block->next = (t_block *)((unsigned char *)block + sizeof(t_block) + \
		block_size);
		block->next->next = END_OF_HEAP_PTR;
		block->next->size = ++block_pos;
		if (block_pos != 1)
			(block - 1)->next = block;
	}
	return (++block);
}

// Designed to work with TINY and SMALL heaps only. Searches for a free block
// in the linked list of blocks and if found populates its metadata and returns
// its payload address. If no free block is found, it creates a new heap (linked
// to previous one) of 'N' PREALLOC_BLOCKS and returns the payload address of
// the first block of the new set (marked as allocated).
static void	*search_free_block(int heap_type, int block_size, size_t mem_req)
{
	t_block	*block;
	size_t	block_position;

	block = (t_block *)g_heaps[heap_type];
	block_position = 0;
	while (block->size & 0x1)
	{
		if (block->next->size == PREALLOC_BLOCKS)
		{
			if (block->next->next == END_OF_HEAP_PTR)
				return (add_tiny_or_small_heap(heap_type, mem_req, block));
			block = block->next->next;
			block_position = 0;
		}
		block = (t_block *)((unsigned char *)block + BLOCK_OVERHEAD + \
			block_size);
		block_position++;
	}
	block->size = mem_req | 1;
	return (set_block_metadata(block, block_size, block_position));
}

// In some literature it is said that mmap rounds up 'size' to the next multiple
// of the system page size, just in case, it is done explicitly.
// Expands LARGE heap creating a new block and attaching it to the end of the 
// linked list of LARGE blocks.
static void	*add_block_to_large_heap(size_t size)
{
	t_block	*block;
	t_block	*new_block;
	size_t	mmap_size;

	mmap_size = size + BLOCK_OVERHEAD;
	mmap_size = (mmap_size + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
	new_block = mmap(NULL, mmap_size, PROT_READ | PROT_WRITE, \
		MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (new_block == MAP_FAILED)
		return (NULL);
	block = (t_block *)g_heaps[LARGE_HEAP];
	while (block->next->next != END_OF_HEAP_PTR)
		block = block->next->next;
	block->next->next = new_block;
	block->next->size = block->size;
	new_block->size = size | 1;
	new_block->next = (t_block *)((unsigned char *)new_block + \
		sizeof(t_block) + size);
	new_block->next->size = END_OF_HEAP_MARKER;
	new_block->next->next = (t_block *)END_OF_HEAP_PTR;
	return (new_block + 1);
}

// Follows SUSv3 specification that malloc(0) may return NULL.
// Memory alignment is sizeof(size_t) * 2 (usually that means 16 bytes),
// alignment achieved adjusting the allocated size to the next multiple of
// MEMORY_ALIGNMENT.
static void	*ft_malloc(size_t size)
{
	if (size == 0)
		return (NULL);
	size = (size + MEMORY_ALIGNMENT - 1) & ~(MEMORY_ALIGNMENT - 1);
	if (size <= TINY_BLOCK_SIZE)
	{
		if (!g_heaps[TINY_HEAP])
			if (!init_tiny_or_small_heap(TINY_HEAP, TINY_HEAP_SIZE))
				return (NULL);
		return (search_free_block(TINY_HEAP, TINY_BLOCK_SIZE, size));
	}
	else if (size <= SMALL_BLOCK_SIZE)
	{
		if (!g_heaps[SMALL_HEAP])
			if (!init_tiny_or_small_heap(SMALL_HEAP, SMALL_HEAP_SIZE))
				return (NULL);
		return (search_free_block(SMALL_HEAP, SMALL_BLOCK_SIZE, size));
	}
	if (!g_heaps[LARGE_HEAP])
		return (init_large_heap(size));
	else
		return (add_block_to_large_heap(size));
}

void	*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	ptr = ft_malloc(size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
