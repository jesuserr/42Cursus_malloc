/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc_tiny_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:33:16 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/20 18:03:01 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/malloc.h"

int	main(void)
{
	void *array[128];
	
	array[0] = malloc(128);                         
	ft_memset(array[0], 'A', 128);
	ft_hex_dump(g_heaps[TINY_HEAP], 256, 64);       // after malloc
	ft_printf("---\n");
    free(array[0]);
    ft_hex_dump(g_heaps[TINY_HEAP], 256, 64);       // after free
    array[0] = calloc(128,1);
    ft_printf("---\n");
    ft_hex_dump(g_heaps[TINY_HEAP], 256, 64);       // after calloc
			
	return (0);
}

// gcc -o calloc_tiny_test calloc_tiny_test.c -L. -L../libft -lft_malloc -lft && ./run_linux.sh ./calloc_tiny_test
