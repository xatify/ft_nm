/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:56:54 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 20:05:42 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <elf.h>
#include "checks.h"

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n);

static int	check_ident(const void *file)
{
	static const unsigned char	ident[] = {
		ELFMAG0,
		ELFMAG1,
		ELFMAG2,
		ELFMAG3,
	};
	const unsigned char			*f;

	f = (const unsigned char *)file;
	if (ft_memcmp(f, ident, sizeof(ident)))
	{
		return (NOIDENT);
	}
	return (VALID);
}

static int	check_class(const void *file)
{
	const unsigned char	*f;

	f = (const unsigned char *)file;
	if (f[EI_CLASS] != ELFCLASS32 && f[EI_CLASS] != ELFCLASS64)
	{
		return (NOCLASS);
	}
	return (VALID);
}

static int	check_encoding(const void *file)
{
	const unsigned char	*f;

	f = (const unsigned char *)file;
	if (f[EI_DATA] != ELFDATA2LSB)
	{
		return (NOENCOD);
	}
	return (VALID);
}

int	check_header(const void *file)
{
	return (check_ident(file) | check_class(file) | check_encoding(file));
}
