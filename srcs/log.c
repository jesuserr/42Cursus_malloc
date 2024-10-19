/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:08:07 by jesuserr          #+#    #+#             */
/*   Updated: 2024/10/19 14:16:14 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <fcntl.h>

// Same as function in show_alloc_mem.c, except adapted to write to a file
// descriptor instead of stdout. As the referenced function, is not protected
// for values of 'nbr' equal to zero.
static void	print_size_t_as_digits_fd(int fd, size_t nbr)
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
		ft_putnbr_fd(digits[i++], fd);
		leading_zero = false;
	}
	ft_putstr_fd(" bytes", fd);
}

static void	ft_put_hex_nbr_fd(int fd, size_t n)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n >= 16)
	{
		ft_put_hex_nbr_fd(fd, n / 16);
		ft_putchar_fd(hex[n % 16], fd);
	}
	else
		ft_putchar_fd(hex[n], fd);
}

// Checks if the pointer is inside the range of the heap preallocated at the
// beginning of the program (for TINY and SMALL heaps only). Allows to be more
// specific in the log message indicating if the block involved is located in
// the preallocated heap or not.
static void	is_ptr_in_preallocated_heap(void *ptr, int heap_type, int fd)
{
	void	*start_address;
	void	*end_address;

	start_address = g_heaps[heap_type];
	if (heap_type == TINY_HEAP)
		end_address = start_address + TINY_HEAP_SIZE;
	else if (heap_type == SMALL_HEAP)
		end_address = start_address + SMALL_HEAP_SIZE;
	if (ptr >= start_address && ptr < end_address)
		ft_putstr_fd(" on preallocated ", fd);
	else
		ft_putstr_fd(" on ", fd);
}

// Formats the message to be written to the log file. If the size is zero and
// the pointer is NULL, the log message is written as it is.
static void	text_to_write(int fd, char *log, size_t size, void *ptr)
{
	if (size == 0 && ptr == NULL)
		ft_putstr_fd(log, fd);
	else
	{
		ft_putstr_fd("\n Address [0x", fd);
		ft_put_hex_nbr_fd(fd, (size_t)(ptr));
		ft_putstr_fd("] -> ", fd);
		write(fd, log, ft_strlen(log));
		ft_putchar_fd('\t', fd);
		print_size_t_as_digits_fd(fd, size);
		if (size <= TINY_BLOCK_SIZE)
		{
			is_ptr_in_preallocated_heap(ptr, TINY_HEAP, fd);
			ft_putstr_fd("TINY heap", fd);
		}
		else if (size <= SMALL_BLOCK_SIZE)
		{
			is_ptr_in_preallocated_heap(ptr, SMALL_HEAP, fd);
			ft_putstr_fd("SMALL heap", fd);
		}
		else
			ft_putstr_fd(" on LARGE heap", fd);
	}
}

// Writes the log message to LOG_FILE_NAME. If the environment variable
// CUSTOM_MALLOC_LOG is not set to "1", the function does nothing. If the log
// file cannot be opened or closed, the environment variable CUSTOM_MALLOC_LOG
// is unset to avoid multiple message errors.
void	write_log_to_file(char *log, size_t size, void *ptr)
{
	int		fd;
	char	*env_var;

	env_var = getenv("CUSTOM_MALLOC_LOG");
	if (env_var == NULL || ft_strncmp(env_var, "1", 1) != 0)
		return ;
	fd = open(LOG_FILE_NAME, O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Error opening log file\n", 2);
		unsetenv("CUSTOM_MALLOC_LOG");
		return ;
	}
	text_to_write(fd, log, size, ptr);
	if (close(fd) == -1)
	{
		ft_putstr_fd("Error closing log file\n", 2);
		unsetenv("CUSTOM_MALLOC_LOG");
	}
	return ;
}
