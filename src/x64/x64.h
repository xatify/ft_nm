/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x64.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:59:58 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 19:09:07 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef X64_H
# define X64_H

# include <elf.h>
# include <stddef.h>
# include <stdlib.h>
# include "../object_file.h"
# include "../output.h"

void		*get_64section_by_name(const Elf64_Ehdr *hdr, const char *name);
Elf64_Shdr	*elf64_sheader(const Elf64_Ehdr *hdr);
Elf64_Shdr	*elf64_sheader_idx(const Elf64_Ehdr *hdr, const size_t idx);
Elf64_Shdr	*get64_sheader_by_name(const Elf64_Ehdr *hdr, const char *name);
Elf64_Shdr	*symtab_sh(const Elf64_Ehdr *hdr);
char		*shstr64_lookup_string(const Elf64_Ehdr *hdr, const size_t offset);
Elf64_Shdr	*shstrtab_64header(const Elf64_Ehdr *hdr);
int			get_64symbol( const Elf64_Ehdr *hdr, const Elf64_Sym *sym, \
							t_object_file *file, const char *strtab);
void		iterate_over_64_symtab(const Elf64_Ehdr *hdr, \
									t_object_file *const file);

#endif