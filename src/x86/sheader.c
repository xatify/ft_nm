/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sheader.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:20:31 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 15:23:52 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <elf.h>

/**
 * @brief get the start of the section headers
 * 
 * @param hdr 
 * @return Elf32_Shdr* 
 */
Elf32_Shdr* elf_sheader(Elf32_Ehdr *hdr) {
    return (Elf32_Shdr *)((char *)hdr + hdr->e_shoff);
}

/**
 * @brief get section header by index
 * 
 * @param hdr 
 * @param idx 
 * @return Elf32_Shdr* 
 */
static Elf32_Shdr* elf_sheader_idx(Elf32_Ehdr *hdr, int idx) {
    return elf_sheader(hdr) + idx;
}


/**
 * @brief Get the ssection header by name of the section
 * 
 * @param hdr 
 * @param name 
 * @return Elf32_Shdr* 
 */
static Elf32_Shdr *get_sheader_by_name(Elf32_Ehdr *hdr, const char* name) {
    Elf32_Shdr* sheader;
    char *_name;
    int idx;
    
    sheader = elf_sheader(hdr);
    idx = 0;
    while (idx < hdr->e_shnum) {
        if (idx != SHN_UNDEF) {
            _name = shstr_lookup_string(hdr, sheader->sh_name);
            if (!ft_memcmp(name, _name, ft_strlen(name))) {
                return sheader;
            }
        }
        idx++;
        sheader += 1;
    }
    return NULL;
}