/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shstrtab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:27:08 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 15:28:33 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <elf.h>
#include <stddef.h>


/**
 * @brief get the strtable section header
 * 
 * @param hdr 32bit elf header
 * @return Elf32_Shdr* 
 */
static Elf32_Shdr* shstrtab_header(Elf32_Ehdr *hdr) {
    if (hdr->e_shstrndx != SHN_UNDEF)
        return (elf_sheader_idx(hdr, hdr->e_shstrndx));
    return NULL;
}

/**
 * @brief return section header name from
 * section header string table
 * 
 * @param hdr elf header
 * @param offset offset of the string
 * @return char* pointer to string
 */
static char *shstr_lookup_string(Elf32_Ehdr *hdr, int offset) {
    Elf32_Shdr *sth = shstrtab_header(hdr);
    return (char *)hdr + sth->sh_offset + offset;
}