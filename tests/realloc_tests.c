/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_tests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:33:16 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/20 18:05:16 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/malloc.h"

int	main(void)
{
	void *ptr = malloc(5000);
	if (!ptr)
		ft_printf("ptr is NULL\n");
	else
		ft_printf("ptr: %p\n", ptr);
	ft_memset(ptr, 'A', 5000);
	//ft_hex_dump(ptr - 16, 5000, 64);
	show_alloc_mem();
	void *ptr2 = realloc(ptr, 4000);
	if (!ptr2)
		ft_printf("ptr2 is NULL\n");
	else
		ft_printf("ptr2: %p\n", ptr2);	
	//ft_hex_dump(ptr2 - 16, 6000, 64);
	show_alloc_mem();
	
	void *ptr3 = malloc(128);
	if (!ptr3)
		ft_printf("ptr3 is NULL\n");
	else
		ft_printf("ptr3: %p\n", ptr3);
	ft_memset(ptr3, 'A', 128);
	//ft_hex_dump(ptr - 16, 5000, 64);
	show_alloc_mem();
	void *ptr4 = realloc(ptr3, 1024);
	if (!ptr4)
		ft_printf("ptr4 is NULL\n");
	else
		ft_printf("ptr4: %p\n", ptr4);
	show_alloc_mem();


	return (0);
}

//gcc -o realloc_tests realloc_tests.c -L. -L../libft -lft_malloc -lft && ./run_linux.sh ./realloc_tests
