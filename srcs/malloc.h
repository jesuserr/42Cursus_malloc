/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:50:56 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/17 12:17:45 by jesuserr         ###   ########.fr       */
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
# include <sys/mman.h>						// for mmap, munmap
# include <stdint.h>						// for SIZE_MAX
/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              DEFINES
*/
// Both TINY_HEAP_SIZE and SMALL_HEAP_SIZE are multiples of PAGE_SIZE
# define TINY_BLOCK_SIZE        128
# define SMALL_BLOCK_SIZE       1024
# define BLOCK_OVERHEAD			sizeof(t_block) * 2
# define PREALLOC_BLOCKS    	128
# define TINY_HEAP_SIZE			(TINY_BLOCK_SIZE + BLOCK_OVERHEAD) * \
								PREALLOC_BLOCKS
# define SMALL_HEAP_SIZE		(SMALL_BLOCK_SIZE + BLOCK_OVERHEAD) * \
								PREALLOC_BLOCKS
# define PAGE_SIZE              (int)(getpagesize())
# define MAP_ANONYMOUS        	0x20  	// delete it later (for VSCode error)
# define END_OF_HEAP_MARKER		0x01
# define END_OF_HEAP_PTR		(void *)0xFFFFFFFFFFFFFFFF
# define MEMORY_ALIGNMENT		sizeof(size_t) * 2	// 16 bytes

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

// define my own boolean type
typedef enum s_bool
{
	false,
	true
}	t_bool;

// s_block size is 16 bytes (2 x 8 bytes)
typedef struct s_block
{
	size_t			size;
	struct s_block	*next;
}					t_block;

// global variable to store the three types of heaps
extern void		*g_heaps[3];

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                        FUNCTION PROTOTYPES
*/
/********************************** malloc.c **********************************/

void	*ft_malloc(size_t size);

/********************************** free.c ************************************/

void	ft_free(void *ptr);

/********************************** realloc.c *********************************/

void	*ft_realloc(void *ptr, size_t size);

/********************************** calloc.c **********************************/

void	*ft2_calloc(size_t nmemb, size_t size);

/********************************** inits.c ***********************************/

void	*init_tiny_or_small_heap(int heap_type, size_t heap_size);
void	*add_tiny_or_small_heap(int heap_type, size_t mem_req, t_block *block);
void	*init_large_heap(size_t size);

/********************************** utils.c ***********************************/

void	show_alloc_mem(void);
t_bool	is_heap_empty(t_block *block);

#endif