/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:50:56 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/02 18:02:46 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              HEADERS
*/
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include <sys/mman.h>
# include <stdio.h>	// for printf, remove it

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              DEFINES
*/
//#define DEFAULT_MMAP_MAX 1024
# define TINY_BLOCK_SIZE        128
# define SMALL_BLOCK_SIZE       1024
# define PAGE_SIZE              (int)(getpagesize())
# define PREALLOC_BLOCKS    	128
# define BLOCK_OVERHEAD			sizeof(t_block) * 2
# define MAP_ANONYMOUS        	0x20  //delete it later

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              STRUCTS
*/
// enum types of heap in order to index the g_heaps array
enum	e_heap_type
{
	TINY_HEAP,
	SMALL_HEAP,
	LARGE_HEAP
};

// s_block size is 16 bytes
typedef struct s_block
{
	size_t			size;
	struct s_block	*next;
}					t_block;

// s_heap size is XX bytes - I think I am not going to use it
typedef struct s_heap
{
	size_t			size;	
}					t_heap;

extern void		*g_heaps[3];

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                        FUNCTION PROTOTYPES
*/
void	custom_free(void *ptr);
void	*ft_malloc(size_t size);
void	hex_dump(void *mem, size_t len);

#endif