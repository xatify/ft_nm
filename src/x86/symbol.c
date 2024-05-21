/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:30:40 by abbouzid          #+#    #+#             */
/*   Updated: 2024/05/21 15:34:52 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <elf.h>

/**
 * @brief Get the symbol name from string table
 * 
 * @param hdr header name
 * @param idx index of the string
 * @return char* string pointer
 */
char *get_symbol_name(Elf32_Ehdr *hdr, size_t idx) {
    char *symstrtab = get_section_by_name(hdr, ".strtab");

    if (symstrtab) {
        return symstrtab + idx;
    }
    return NULL;
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
int get_symbol_type(Elf32_Sym *sym, Elf32_Shdr *sheader, char *t) {
    unsigned char bind;
    unsigned char type;

    bind = ELF32_ST_BIND(sym->st_info);
    type = ELF32_ST_TYPE(sym->st_info);

    if (type == STT_FILE) {
        return -1;
    }
    if (bind == STB_WEAK && type == STT_OBJECT) {
        *t = 'V';
        if (sym->st_shndx == SHN_UNDEF)
            *t = 'v';
    }
    else if (bind == STB_WEAK) {
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
    else if (
        sheader->sh_type == SHT_NOBITS &&
        sheader->sh_flags == (SHF_ALLOC | SHF_WRITE)
    )
        *t = 'B';
    else if (sheader->sh_flags == SHF_ALLOC)
        *t = 'R';
    else if (
        sheader->sh_type == SHT_PROGBITS &&
        sheader->sh_flags == (SHF_ALLOC | SHF_EXECINSTR)
    )
        *t = 'T';
    else if (sheader->sh_flags == (SHF_ALLOC | SHF_WRITE))
        *t = 'D';
    else if (sheader->sh_type == SHT_DYNAMIC)
        *t = 'D';
    else
        *t = 'T';
    
    if (bind == STB_LOCAL)
        *t += 32;
    
    return 0;
}

/**
 * @brief Get the symbol value, type, name
 * 
 * @param hdr elf header
 * @param sym symbol header table entry
 * @param symbol pointer to hold the symbol
 * @return int return 0 on success
 */
int get_symbol(Elf32_Ehdr* hdr, Elf32_Sym *sym, t_symbol *symbol) {
    unsigned int value;
    char *name;
    Elf32_Shdr *sheader;
    char t;


    if (sym->st_name) {
        value = sym->st_value;
        name = get_symbol_name(hdr, sym->st_name);
        sheader = elf_sheader_idx(hdr, sym->st_shndx);
        if (get_symbol_type(sym, sheader, &t)) {
            return -1;
        }
        
        if (name && t) {
            symbol->name = name;
            symbol->value = value;
            symbol->type = t;
            return 0;
        }
    }
    return -1;
}
