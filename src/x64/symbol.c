/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:11:20 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 19:04:03 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "x64.h"

static void	wuac(unsigned char type, unsigned char bind, const Elf64_Sym *sym, \
				char *t)
{
	if (bind == STB_WEAK && type == STT_OBJECT)
	{
		*t = 'V';
		if (sym->st_shndx == SHN_UNDEF)
			*t = 'v';
	}
	else if (bind == STB_WEAK)
	{
		*t = 'W';
		if (sym->st_shndx == SHN_UNDEF)
			*t = 'w';
	}
	else if (sym->st_shndx == SHN_UNDEF)
		*t = 'U';
	else if (sym->st_shndx == SHN_ABS)
		*t = 'A';
	else if (sym->st_shndx == SHN_COMMON)
		*t = 'C';
}

static void	data_and_text(const Elf64_Shdr *sheader, char *t)
{
	if (
		sheader->sh_type == SHT_NOBITS && \
		sheader->sh_flags == (SHF_ALLOC | SHF_WRITE)
	)
		*t = 'B';
	else if (sheader->sh_flags == SHF_ALLOC)
		*t = 'R';
	else if (
		sheader->sh_type == SHT_PROGBITS && \
		sheader->sh_flags == (SHF_ALLOC | SHF_EXECINSTR)
	)
		*t = 'T';
	else if (sheader->sh_flags == (SHF_ALLOC | SHF_WRITE))
		*t = 'D';
	else if (sheader->sh_type == SHT_DYNAMIC)
		*t = 'D';
	else
		*t = 'T';
}

int	get_64symbol_type(const Elf64_Sym *sym, const Elf64_Shdr *sheader, char *t)
{
	unsigned char	bind;
	unsigned char	type;

	bind = ELF64_ST_BIND(sym->st_info);
	type = ELF64_ST_TYPE(sym->st_info);
	*t = '\0';
	if (type == STT_FILE)
		return (-1);
	wuac(type, bind, sym, t);
	if (*t)
		return (0);
	data_and_text(sheader, t);
	if (bind == STB_LOCAL)
		*t += 32;
	return (0);
}

int	get_64symbol( const Elf64_Ehdr *hdr, const Elf64_Sym *sym, \
				t_object_file *file, const char *strtab)
{
	Elf64_Shdr	*sheader;
	t_symbol	*symbol;
	char		*name;
	char		t;

	symbol = get_next_empty_symbol(file);
	if (sym->st_name)
	{
		name = (char *)strtab + sym->st_name;
		sheader = elf64_sheader_idx(hdr, sym->st_shndx);
		if (get_64symbol_type(sym, sheader, &t))
			return (-1);
		if (*name && t)
		{
			symbol->name = name;
			symbol->value = sym->st_value;
			symbol->type = t;
			return (0);
		}
	}
	return (-1);
}
