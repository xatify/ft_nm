/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:34:37 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 14:39:14 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *lhs, const void *rhs, size_t size);

char	*ft_strdup(const char *lhs)
{
	size_t	size;
	char	*rhs;

	size = ft_strlen(lhs);
	rhs = (char *)malloc(size + 1);
	if (!rhs)
		return (rhs);
	return (ft_memcpy(rhs, lhs, size + 1));
}
