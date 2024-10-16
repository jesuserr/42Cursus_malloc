/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:01:21 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/16 20:44:13 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// The realloc() function changes the size of the memory block pointed to by ptr
// to size bytes. The contents will be unchanged in the range from the start of
// the region up to the minimum of the old and new sizes. If the new size is
// larger than the old size, the added memory will not be initialized. If ptr is
// NULL, then the call is equivalent to malloc(size), for all values of size;
// if size is equal to zero, and ptr is not NULL, then the call is equivalent
// to free(ptr). Unless ptr is NULL, it must have been returned by an earlier
// call to malloc(), calloc(), or realloc(). If the area pointed to was moved,
// a free(ptr) is done.

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;	

	if (!ptr)
		return (ft_malloc(size));
	if (ptr && size == 0)
	{
		ft_free(ptr);
		return (NULL);
	}
	new_ptr = ft_malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	ft_free(ptr);
	return (new_ptr);
}
// On success, realloc() returns a pointer to the location of the resized block.
// This may be different from its location before the call. On error, realloc()
// returns NULL and leaves the block pointed to by ptr untouched (SUSv3 requires
// this).
// When realloc() increases the size of a block of allocated memory, it doesn’t
// initialize the additionally allocated bytes.