/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x64.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:12:58 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 21:55:52 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "x64.h"

void	iterate_over_64_symtab(const Elf64_Ehdr *hdr, t_object_file *const file)
{
	Elf64_Shdr	*sheader;
	char		*strtab;
	size_t		idx;

	sheader = symtab_sh(hdr);
	if (!sheader)
	{
		print_error(file->name, "no symbols");
		return ;
	}
	init_symbol_array(file, sheader->sh_size / sheader->sh_entsize);
	strtab = (char *)get_64section_by_name(hdr, ".strtab");
	idx = 0;
	while (idx < (sheader->sh_size / sheader->sh_entsize))
	{
		if (idx != STN_UNDEF)
		{
			if (get_64symbol(hdr, (Elf64_Sym *)((char *)hdr + \
			sheader->sh_offset) + idx, file, strtab) == 0)
			{
				file->sym_num += 1;
			}
		}
		idx++;
	}
}

void	iterator_64(t_object_file *file)
{
	iterate_over_64_symtab((const Elf64_Ehdr *)file->content, file);
}
