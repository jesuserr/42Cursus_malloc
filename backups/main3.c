/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:33:16 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/14 20:46:32 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int	main(void)
{
    void *array[1000];	
	for (int i = 0; i < 257; i++)
	{
        array[i] = ft_malloc(128);
        if (array[i] == NULL)
            return (1);
		ft_memset(array[i], i, 128);        
	}

    
    ft_hex_dump(array[0] - 16, 512 , 64);
    ft_printf("\n");    
    ft_hex_dump(array[127] - 16, 256 , 64);
    ft_printf("\n");    
    ft_hex_dump(array[128] - 16, 256 + 16, 64);
    ft_printf("\n");    
    ft_hex_dump(array[255] - 16, 256 , 64);
    ft_printf("\n");    
    ft_hex_dump(array[256] - 16, 512 , 64);
    ft_printf("\n");    
    

    return (0);
    
    ft_hex_dump(g_heaps[SMALL_HEAP], 2048 + 16, 64);	
    ft_printf("\n");    
    ft_hex_dump(g_heaps[SMALL_HEAP] + 135168 - 2048, 2048 + 16, 64);	
    
	
    //void *ptr= ft_malloc(12);
    //(void)ptr;
    //ft_hex_dump(g_heaps[TINY_HEAP], 1024 + 16, 64);
    //ft_hex_dump(g_heaps[TINY_HEAP], 20480, 64);
    /*
    void *ptr = ft_malloc(128);
    ft_memset(ptr, 'A', 128);    
    void *ptr2 = ft_malloc(128);
    ft_memset(ptr2, 'B', 128);
    void *ptr3 = ft_malloc(128);
    ft_memset(ptr3, 'C', 128);
        
    ft_hex_dump(g_heaps[TINY_HEAP], 1024, 64);
    */
    //show_alloc_mem();
	return (0);
}

// make && ./allocator | grep "128 bytes" | wc -l -> should return 384
// make && valgrind --leak-check=full ./allocator
// make && strace ./allocator 2>&1 | grep mmap
// make && /usr/bin/time -v ./allocator 0.00
