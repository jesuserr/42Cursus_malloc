/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:16:37 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/09 12:49:02 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// ft_printf does not support size_t, so it is casted to unsigned int
// hopefully nobody will allocate more than 4GB of memory in total.
size_t	print_used_blocks(t_block *block, size_t total_bytes_used)
{
	t_bool	block_in_use;
	size_t	bytes_in_use;

	block_in_use = block->size & 0x1;
	bytes_in_use = block->size & ~0x1;
	while (block->next->next != END_OF_HEAP_PTR)
	{
		if (block_in_use)
		{
			ft_printf("%p - %p : %u bytes\n", block + 1, block->next, \
				(unsigned int)bytes_in_use);
			total_bytes_used += bytes_in_use;
		}
		block = block->next->next;
		block_in_use = block->size & 0x1;
		bytes_in_use = block->size & ~0x1;
	}
	if (block_in_use)
	{
		ft_printf("%p - %p : %u bytes\n", block + 1, block->next, \
			(unsigned int)bytes_in_use);
		total_bytes_used += bytes_in_use;
	}
	return (total_bytes_used);
}

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
		ft_printf("%s : %p\n", heap_names[i], g_heaps[i]);
		block = (t_block *)g_heaps[i];
		total_bytes_used = print_used_blocks(block, total_bytes_used);
		i++;
	}
	ft_printf("Total : %u bytes\n", (unsigned int)total_bytes_used);
}
