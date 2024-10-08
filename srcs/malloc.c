/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:12:45 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/08 14:09:13 by jesuserr         ###   ########.fr       */
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
	ft_printf("No free block found\n");
	return (NULL);
}

// In some literature it is said that mmap rounds up 'size' to the next multiple
// of the system page size, just in case, it is done explicitly.
// Expands LARGE heap creating a new block and attaching it to the end of the 
// linked list of LARGE blocks.
void	*add_block_to_large_heap(size_t size)
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
void	*ft_malloc(size_t size)
{
	if (size == 0)
		return (NULL);
	if (!g_heaps[TINY_HEAP] && !g_heaps[SMALL_HEAP])
		if (!init_tiny_small_heaps())
			return (NULL);
	size = (size + MEMORY_ALIGNMENT - 1) & ~(MEMORY_ALIGNMENT - 1);
	if (size <= TINY_BLOCK_SIZE)
		return (search_free_block(TINY_HEAP, size));
	else if (size <= SMALL_BLOCK_SIZE)
		return (search_free_block(SMALL_HEAP, size));
	else
	{
		if (!g_heaps[LARGE_HEAP])
			return (init_large_heap(size));
		else
			return (add_block_to_large_heap(size));
	}
}
