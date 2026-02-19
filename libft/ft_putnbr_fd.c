/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:12:09 by coholbur          #+#    #+#             */
/*   Updated: 2025/01/31 14:05:57 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putnbr_fd((n % 10), fd);
	}
	else
	{
		ft_putchar_fd((n + '0'), fd);
	}
}

// int	main(void)
// {
// 	// 	int fd = open("./test.c", O_CREAT | O_WRONLY, 0777);
// 	// ft_putchar_fd('c', fd);
// 	// 	printf(" %d\n", fd);
// 	// 	close(fd);
// 	// 	//ft_putnbr_fd(2147483648, 1);
// 	ft_putnbr_fd(1, 1);
// 	printf("\n");
// 	ft_putnbr_fd(-9, 1);
// 	printf("\n");
// 	ft_putnbr_fd(-1000, 1);
// 	printf("\n");
// 	ft_putnbr_fd(-0, 1);
// 	printf("\n");
// 	ft_putnbr_fd(-2147483648, 1);
// 	return (0);
// }
