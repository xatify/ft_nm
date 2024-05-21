/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:58:13 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 00:20:10 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ascii.h"


size_t	ft_strlen(const char *str);

int	ft_strcmp(const char *_s1, const char *_s2)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)_s1;
	s2 = (unsigned char *)_s2;
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			break ;
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

static void	no_special(const char *_s1, char *s1)
{
	size_t	i;
	int	j;

	j = 0;
	i = 0;
	while (i < ft_strlen(_s1))
	{
		if (ft_isalnum(_s1[i]))
		{
			s1[j] = to_lower(_s1[i]);
			j++;
		}
		i++;
	}
	s1[j] = '\0';
}

int	ft_stralnumcmp(const char *_s1, const char *_s2)
{
	char	*s1;
	char	*s2;
	int		ret;

	s1 = malloc(ft_strlen(_s1) + 1);
	no_special(_s1, s1);
	s2 = malloc(ft_strlen(_s2) + 1);
	no_special(_s2, s2);
	ret = ft_strcmp(s1, s2);
	free(s1);
	free(s2);
	return (ret);
}
