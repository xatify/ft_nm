/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:22:13 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 23:39:33 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	hexadigit(int n)
{
	if (n < 10)
		return ('0' + n);
	return ('a' + (n - 10));
}

void	hexa_rep(size_t n, int size, char c, char *buf)
{
	buf[size] = '\0';
	while (size--)
		*buf++ = c;
	while (n)
	{
		*--buf = hexadigit(n % 16);
		n = n / 16;
	}
}
