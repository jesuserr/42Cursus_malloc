/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:33:16 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/16 20:15:54 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int	main(void)
{
	void *ptr = ft_malloc(5000);
	if (!ptr)
		ft_printf("ptr is NULL\n");
	else
		ft_printf("ptr: %p\n", ptr);
	ft_memset(ptr, 'A', 5000);
	//ft_hex_dump(ptr - 16, 5000, 64);
	show_alloc_mem();
	void *ptr2 = ft_realloc(ptr, 4000);
	if (!ptr2)
		ft_printf("ptr2 is NULL\n");
	else
		ft_printf("ptr2: %p\n", ptr2);	
	//ft_hex_dump(ptr2 - 16, 6000, 64);
	show_alloc_mem();
	
	void *ptr3 = ft_malloc(128);
	if (!ptr3)
		ft_printf("ptr3 is NULL\n");
	else
		ft_printf("ptr3: %p\n", ptr3);
	ft_memset(ptr3, 'A', 128);
	//ft_hex_dump(ptr - 16, 5000, 64);
	show_alloc_mem();
	void *ptr4 = ft_realloc(ptr3, 1024);
	if (!ptr4)
		ft_printf("ptr4 is NULL\n");
	else
		ft_printf("ptr4: %p\n", ptr4);
	show_alloc_mem();


	return (0);
}

// make && valgrind --leak-check=full ./allocator
// make && strace ./allocator 2>&1 | grep mmap
// make && /usr/bin/time -v ./allocator 0.00
// NOTES
// - gestion de errores
// - realloc
// - git submodule update --remote libft
// - getrlimit purpose?
