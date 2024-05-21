/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x86.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:33:39 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 21:54:58 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "x86.h"

/**
 * @brief iterate over symbol table of 32 bit object file
 *  and populate the symbols array in file struct
 * 
 * @param hdr elf header
 * @param file 
 */
void	iterate_over_32_symtab(Elf32_Ehdr *hdr, t_object_file *file)
{
	Elf32_Shdr	*sheader;
	char		*strtab;
	size_t		idx;

	sheader = get_sheader_by_name(hdr, ".symtab");
	if (!sheader)
	{
		print_error(file->name, "no symbols");
		return ;
	}
	init_symbol_array(file, sheader->sh_size / sheader->sh_entsize);
	strtab = (char *)get_section_by_name(hdr, ".strtab");
	idx = 0;
	while (idx < (sheader->sh_size / sheader->sh_entsize))
	{
		if (idx != STN_UNDEF)
		{
			if (get_symbol(hdr, (Elf32_Sym *)((char *)hdr + \
				sheader->sh_offset) + idx, file, strtab) == 0)
			{
				file->sym_num += 1;
			}
		}
		idx++;
	}
}

void	iterator_32(t_object_file *file)
{
	iterate_over_32_symtab((Elf32_Ehdr *)file->content, file);
}
