/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:13:44 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/01 19:14:33 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	custom_free(void *ptr)
{
	int	result;

	if (!ptr)
		return ;
	result = munmap(ptr, getpagesize());
	ft_printf("munmap result: %d\n", result);
}
