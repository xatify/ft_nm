/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sheader.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:00:37 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 18:41:43 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "x64.h"

int		ft_memcmp(const void *lhs, const void *rhs, size_t size);
size_t	ft_strlen(const char *str);

Elf64_Shdr	*elf64_sheader(const Elf64_Ehdr *hdr)
{
	return ((Elf64_Shdr *)((char *)hdr + hdr->e_shoff));
}

Elf64_Shdr	*elf64_sheader_idx(const Elf64_Ehdr *hdr, const size_t idx)
{
	return (elf64_sheader(hdr) + idx);
}

Elf64_Shdr	*get64_sheader_by_name(const Elf64_Ehdr *hdr, const char *name)
{
	Elf64_Shdr	*sheader;
	char		*_name;
	size_t		idx;

	sheader = elf64_sheader(hdr);
	idx = 0;
	while (idx < hdr->e_shnum)
	{
		if (idx != SHN_UNDEF)
		{
			_name = shstr64_lookup_string(hdr, sheader->sh_name);
			if (!ft_memcmp(name, _name, ft_strlen(name)))
			{
				return (sheader);
			}
		}
		idx++;
		sheader++;
	}
	return (NULL);
}

Elf64_Shdr	*symtab_sh(const Elf64_Ehdr *hdr)
{
	Elf64_Shdr	*sheader;
	size_t		i;

	sheader = elf64_sheader(hdr);
	i = 0;
	while (i < hdr->e_shnum)
	{
		if (i != SHN_UNDEF)
		{
			if (sheader->sh_type == SHT_SYMTAB)
			{
				return (sheader);
			}
		}
		sheader++;
		i++;
	}
	return (NULL);
}
