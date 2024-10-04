/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:50:56 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/04 15:43:13 by jesuserr         ###   ########.fr       */
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
# define END_OF_HEAP_MARKER		0x01
# define END_OF_HEAP_PTR		0xFFFFFFFFFFFFFFFF

# define BLUE       			"\033[0;94m"
# define RESET      			"\033[0m"
# define GREY	   				"\033[0;90m"
# define LIGHT_WHITE			"\033[0;97m"

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
void	hex_dump(void *mem, size_t len, size_t bytes_per_line);
void	print_hex_bytes(unsigned char byte);

#endif