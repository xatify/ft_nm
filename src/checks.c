/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:03:03 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 20:09:59 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checks.h"
#include <elf.h>

int	get_class(const void *file)
{
	const unsigned char	*f;

	f = (const unsigned char *)file;
	return (f[EI_CLASS]);
}

int	check_32_format(const void *file, int size)
{
	Elf32_Ehdr	*hdr;

	if (size <= (int) sizeof(Elf32_Ehdr))
	{
		return (1);
	}
	hdr = (Elf32_Ehdr *)file;
	if (hdr->e_phoff >= (unsigned int)size || \
		hdr->e_shoff >= (unsigned int)size)
	{
		return (NOVALID);
	}
	return (VALID);
}

int	check_64_format(const void *file, int size)
{
	Elf64_Ehdr	*hdr;

	if (size <= (int) sizeof(Elf64_Ehdr))
	{
		return (1);
	}
	hdr = (Elf64_Ehdr *)file;
	if (hdr->e_phoff >= (unsigned int)size || \
		hdr->e_shoff >= (unsigned int)size)
	{
		return (NOVALID);
	}
	return (VALID);
}
