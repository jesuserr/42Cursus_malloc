/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:16:37 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/11 18:52:14 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// Function needed because my ft_printf does not support 'size_t' printing.
// It is assumed that 'nbr' will be 64-bit unsigned integer and therefore, 20
// digits will be enough to represent its maximum value. Function not protected
// for values of 'nbr' equal to zero, it must be checked by calling function.
// Reason: I wanted to respect 25 lines max per function according Norminette.
void	print_size_t_as_digits(size_t nbr)
{
	int		digits[20];
	int		i;
	t_bool	leading_zero;

	i = 0;
	while (i < 20)
		digits[i++] = 0;
	i = 19;
	digits [i--] = nbr % 10;
	nbr = nbr / 10;
	while (nbr >= 10)
	{
		digits[i--] = nbr % 10;
		nbr = nbr / 10;
	}
	digits[i--] = (int)nbr;
	leading_zero = true;
	while (i < 20)
	{
		while (digits[i] == 0 && leading_zero)
			i++;
		ft_printf("%d", digits[i++]);
		leading_zero = false;
	}
	ft_printf(" bytes%s\n", RESET);
}

// For preallocated heaps (SMALL and TINY), prints the full range of memory
// address of the preallocated block and the size in bytes of the requested
// memory in the malloc call (adjusted to MEMORY_ALIGNMENT), not the full size
// of the preallocated block.
size_t	print_used_blocks(t_block *block, size_t total_bytes_used, int heap)
{
	size_t	bytes_in_use;

	bytes_in_use = block->size & ~0x1;
	while (block->next->next != END_OF_HEAP_PTR)
	{
		if (block->size & 0x1)
		{
			if (heap == LARGE_HEAP)
				ft_printf("%sLARGE : %p%s\n", BLUE, block, RESET);
			ft_printf("%p - %p : ", block + 1, block->next);
			print_size_t_as_digits(bytes_in_use);
			total_bytes_used += bytes_in_use;
		}
		block = block->next->next;
		bytes_in_use = block->size & ~0x1;
	}
	if (block->size & 0x1)
	{
		if (heap == LARGE_HEAP)
			ft_printf("%sLARGE : %p%s\n", BLUE, block, RESET);
		ft_printf("%p - %p : ", block + 1, block->next);
		print_size_t_as_digits(bytes_in_use);
		total_bytes_used += bytes_in_use;
	}
	return (total_bytes_used);
}

// Prints allocated blocks in each heap and the total bytes used.
void	show_alloc_mem(void)
{
	const char	*heap_names[] = {"TINY", "SMALL", "LARGE"};
	int			heaps_to_read;
	int			i;
	size_t		total_bytes_used;
	t_block		*block;

	if (!g_heaps[TINY_HEAP] && !g_heaps[SMALL_HEAP])
		return ;
	heaps_to_read = 2;
	if (g_heaps[LARGE_HEAP])
		heaps_to_read = 3;
	i = 0;
	total_bytes_used = 0;
	while (i < heaps_to_read)
	{
		if (i < LARGE_HEAP)
			ft_printf("%s%s : %p%s\n", BLUE, heap_names[i], g_heaps[i], RESET);
		block = (t_block *)g_heaps[i];
		total_bytes_used = print_used_blocks(block, total_bytes_used, i++);
	}
	ft_printf("%sTotal : ", BLUE);
	if (total_bytes_used == 0)
		ft_printf("0 bytes%s\n", RESET);
	else
		print_size_t_as_digits(total_bytes_used);
}

// Checks if the block is inside the range of the heap preallocated at the
// beginning of the program. Returns true if it is inside, false otherwise.
// Since we are not unmmapping the preallocated heaps, this function is used to
// avoid checking if the heap is empty when the block is inside a preallocated
// heap.
t_bool	is_block_in_preallocated_heap(t_block *block, int heap_type)
{
	void	*start_address;
	void	*end_address;

	start_address = g_heaps[heap_type];
	if (heap_type == TINY_HEAP)
		end_address = start_address + TINY_HEAP_SIZE;
	else if (heap_type == SMALL_HEAP)
		end_address = start_address + SMALL_HEAP_SIZE;
	if ((void *)block >= start_address && (void *)block < end_address)
		return (true);
	return (false);
}
