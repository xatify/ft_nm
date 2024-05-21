/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:30:40 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 19:49:54 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "x86.h"

/**
 * @brief Get the symbol name from string table
 * 
 * @param hdr header name
 * @param idx index of the string
 * @return char* string pointer
 */
char	*get_symbol_name(Elf32_Ehdr *hdr, size_t idx)
{
	char	*symstrtab;

	symstrtab = get_section_by_name(hdr, ".strtab");
	if (symstrtab)
	{
		return (symstrtab + idx);
	}
	return (NULL);
}

static void	wuac(unsigned char type, unsigned char bind, const Elf32_Sym *sym, \
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

static void	data_and_text(const Elf32_Shdr *sheader, char *t)
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

/**
 * @brief Get the symbol type unsing the type and binding, and section
 * attributes
 * 
 * @param sym symbol table entry 
 * @param sheader section header of the symbol
 * @param t char pointer to return the type
 * @return int return 0 in case of success
 */
int	get_symbol_type(Elf32_Sym *sym, Elf32_Shdr *sheader, char *t)
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

/**
 * @brief Get the symbol value, type, name
 * 
 * @param hdr elf header
 * @param sym symbol header table entry
 * @param symbol pointer to hold the symbol
 * @return int return 0 on success
 */
int	get_symbol(Elf32_Ehdr *hdr, Elf32_Sym *sym, \
			t_object_file *file, const char *strtab)
{
	Elf32_Shdr		*sheader;
	t_symbol		*symbol;
	char			*name;
	char			t;

	symbol = get_next_empty_symbol(file);
	if (sym->st_name)
	{
		name = (char *)strtab + sym->st_name;
		sheader = elf_sheader_idx(hdr, sym->st_shndx);
		if (get_symbol_type(sym, sheader, &t))
		{
			return (-1);
		}
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
