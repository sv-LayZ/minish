/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregnaut <mregnaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:11:44 by mregnaut          #+#    #+#             */
/*   Updated: 2024/11/08 16:25:01 by mregnaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			digit;
	unsigned int	number;

	if (n <= -1)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	number = n;
	if (number <= 9)
	{
		digit = number + '0';
		ft_putchar_fd(digit, fd);
	}
	else
	{
		ft_putnbr_fd(number / 10, fd);
		ft_putnbr_fd(number % 10, fd);
	}
}
