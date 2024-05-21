/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:14:56 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 14:26:31 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_memswap(void *vl, void *vr, int size)
{
	char	*pl;
	char	*pr;
	char	c;

	pl = (char *)vl;
	pr = (char *)vr;
	while (size--)
	{
		c = *pl;
		*pl = *pr;
		*pr = c;
		pl++;
		pr++;
	}
}
