/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shstrtab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:07:51 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 18:44:43 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "x64.h"

Elf64_Shdr	*shstrtab_64header(const Elf64_Ehdr *hdr)
{
	if (hdr->e_shstrndx != SHN_UNDEF)
	{
		return (elf64_sheader_idx(hdr, hdr->e_shstrndx));
	}
	return (NULL);
}

char	*shstr64_lookup_string(const Elf64_Ehdr *hdr, const size_t offset)
{
	Elf64_Shdr	*sth;

	sth = shstrtab_64header(hdr);
	return ((char *)hdr + sth->sh_offset + offset);
}
