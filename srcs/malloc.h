/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:50:56 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/06 20:54:04 by jesuserr         ###   ########.fr       */
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
# include <stdio.h> 						// for printf, delete it later

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              DEFINES
*/
//#define DEFAULT_MMAP_MAX 		1024
# define TINY_BLOCK_SIZE        128
# define SMALL_BLOCK_SIZE       1024
# define PAGE_SIZE              (int)(getpagesize())
# define PREALLOC_BLOCKS    	128
# define BLOCK_OVERHEAD			sizeof(t_block) * 2
# define MAP_ANONYMOUS        	0x20  	// delete it later (for VSCode error)
# define END_OF_HEAP_MARKER		0x01
# define END_OF_HEAP_PTR		0xFFFFFFFFFFFFFFFF
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
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);
void	*ft_realloc(void *ptr, size_t size);
void	*init_heaps(void);

#endif