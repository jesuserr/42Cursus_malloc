/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:12:45 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/02 16:30:31 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// Global variables are automatically initialized to zero if they are not
// explicitly initialized.
void	*g_heaps[3];

// Returning a sentinel value like (void *)1 is a common practice to indicate
// success in functions that return pointers.
void	*heaps_preallocation(void)
{
	unsigned int	real_tiny_size;
	unsigned int	real_small_size;

	real_tiny_size = (TINY_BLOCK_SIZE + BLOCK_OVERHEAD) * PREALLOC_BLOCKS;
	real_small_size = (SMALL_BLOCK_SIZE + BLOCK_OVERHEAD) * PREALLOC_BLOCKS;
	ft_printf("Tiny Size: %d\n", real_tiny_size);
	ft_printf("Small Size: %d\n", real_small_size);
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

// returning sentinel value, modify it later with real pointer
void	*ft_malloc(size_t size)
{
	if (!g_heaps[TINY_HEAP] && !g_heaps[SMALL_HEAP])
		if (!heaps_preallocation())
			return (NULL);
	if (size == 0)
		return (NULL);
	return ((void *)1);
}
