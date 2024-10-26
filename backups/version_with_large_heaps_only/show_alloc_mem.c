/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:16:37 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/26 20:36:14 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// Function needed because my ft_printf does not support 'size_t' printing.
// It is assumed that 'nbr' will be 64-bit unsigned integer and therefore, 20
// digits will be enough to represent its maximum value. Function not protected
// for values of 'nbr' equal to zero, it must be checked by calling function.
// Reason: I wanted to respect 25 lines max per function according Norminette.
static void	print_size_t_as_digits(size_t nbr)
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

static
size_t	print_used_blocks(t_block *block, size_t total_bytes_used)
{
	size_t	bytes_in_use;

	bytes_in_use = block->size;
	while (block->next->next != END_OF_HEAP_PTR)
	{
		ft_printf("%sLARGE : %p%s\n", BLUE, block, RESET);
		ft_printf("%p - %p : ", block + 1, block->next);
		print_size_t_as_digits(bytes_in_use);
		total_bytes_used += bytes_in_use;
		block = block->next->next;
		bytes_in_use = block->size;
	}
	ft_printf("%sLARGE : %p%s\n", BLUE, block, RESET);
	ft_printf("%p - %p : ", block + 1, block->next);
	print_size_t_as_digits(bytes_in_use);
	total_bytes_used += bytes_in_use;
	return (total_bytes_used);
}

// Prints allocated blocks in each heap and the total bytes used.
void	show_alloc_mem(void)
{
	size_t		total_bytes_used;
	t_block		*block;

	pthread_mutex_lock(&g_mutex);
	total_bytes_used = 0;
	if (g_heaps[LARGE_HEAP])
	{
		block = (t_block *)g_heaps[LARGE_HEAP];
		total_bytes_used = print_used_blocks(block, total_bytes_used);
	}
	ft_printf("%sTotal : ", BLUE);
	if (total_bytes_used == 0)
		ft_printf("0 bytes%s\n", RESET);
	else
		print_size_t_as_digits(total_bytes_used);
	pthread_mutex_unlock(&g_mutex);
}
