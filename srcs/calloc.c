/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:52:51 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/18 23:30:20 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// The calloc() function allocates memory for an array of nmemb elements of size
// bytes each and returns a pointer to the allocated memory. The memory is set
// to zero. If nmemb or size is 0, then calloc() returns either NULL, or a 
// unique pointer value that can later be successfully passed to free(). If the
// multiplication of nmemb and size would result in integer overflow, 
// then calloc() returns an error. By contrast, an integer overflow would not be
// detected in the following call to malloc(), with the result that an
// incorrectly sized block of memory would be allocated: malloc(nmemb * size);

// RETURN VALUE - The malloc() and calloc() functions return a pointer to the 
// allocated memory, which is suitably aligned for any built-in type. On error,
// these functions return NULL. NULL may also be returned by a successful call
// to malloc() with a size of zero, or by a successful call to calloc() with
// nmemb or size equal to zero.

void	*calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	int		total_bytes;

	if (nmemb == 0 || size == 0)
		return (NULL);
	total_bytes = nmemb * size;
	if (total_bytes / nmemb != size)
		return (NULL);
	pthread_mutex_lock(&g_mutex);
	write_log_to_file("\nCalloc:", 0, NULL);
	pthread_mutex_unlock(&g_mutex);
	ptr = malloc(total_bytes);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_bytes);
	return (ptr);
}
