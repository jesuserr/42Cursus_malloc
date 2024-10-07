/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:12:45 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/07 10:08:51 by jesuserr         ###   ########.fr       */
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
	printf("No free block found\n");
	return (NULL);
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
		if (!init_heaps())
			return (NULL);
	size = (size + MEMORY_ALIGNMENT - 1) & ~(MEMORY_ALIGNMENT - 1);
	if (size <= TINY_BLOCK_SIZE)
		return (search_free_block(TINY_HEAP, size));
	else if (size <= SMALL_BLOCK_SIZE)
		return (search_free_block(SMALL_HEAP, size));
	else
		printf("Goes to LARGE\n");
	return ((void *)1);
}
// ** returning sentinel value, modify it later with real pointer **