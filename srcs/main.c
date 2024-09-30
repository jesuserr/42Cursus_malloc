/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:33:16 by jesuserr          #+#    #+#             */
/*   Updated: 2024/09/30 17:12:11 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*custom_malloc(size_t size)
{
	void	*ptr;

	ft_printf("Requested Size: %d\n", size);
	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, \
		MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
}

void	custom_free(void *ptr)
{
	int	result;

	if (!ptr)
		return ;
	result = munmap(ptr, getpagesize());
	ft_printf("munmap result: %d\n", result);
}

int	main(void)
{
	char	*str;

	ft_printf("System Page Size: %d\n", getpagesize());
	str = custom_malloc(getpagesize());
	if (!str)
		return (1);
	ft_printf("Returned pointer: %p\n", str);
	ft_memset(str, 'A', getpagesize() + 0);
	custom_free(str);
	return (0);
}

// make && valgrind --leak-check=full ./allocator
// make && strace ./allocator 2>&1 | grep mmap