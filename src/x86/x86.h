/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x86.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:16:38 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 21:37:45 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef X86_H
# define X86_H

# include <elf.h>
# include <stddef.h>
# include <stdlib.h>
# include "../object_file.h"
# include "../output.h"

void		*get_section_by_name(Elf32_Ehdr *hdr, const char *name);
Elf32_Shdr	*elf_sheader(Elf32_Ehdr *hdr);
Elf32_Shdr	*elf_sheader_idx(Elf32_Ehdr *hdr, int idx);
Elf32_Shdr	*get_sheader_by_name(Elf32_Ehdr *hdr, const char *name);
Elf32_Shdr	*shstrtab_header(Elf32_Ehdr *hdr);
char		*shstr_lookup_string(Elf32_Ehdr *hdr, int offset);
char		*get_symbol_name(Elf32_Ehdr *hdr, size_t idx);
int			get_symbol_type(Elf32_Sym *sym, Elf32_Shdr *sheader, char *t);
int			get_symbol(Elf32_Ehdr *hdr, Elf32_Sym *sym, t_object_file *file, \
						const char *strtab);
void		iterate_over_32_symtab(Elf32_Ehdr *hdr, t_object_file *file);
void		iterator_32(t_object_file *file);

#endif