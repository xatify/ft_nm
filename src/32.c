#include "ft_nm.h"


/**
 * @brief get the start of the section headers
 * 
 * @param hdr 
 * @return Elf32_Shdr* 
 */
static Elf32_Shdr* elf_sheader(Elf32_Ehdr *hdr) {
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

static void *get_section_by_name(Elf32_Ehdr *hdr, const char *name) {
    Elf32_Shdr *sheader;

    sheader = get_sheader_by_name(hdr, name);
    if (sheader) {
        return ((char *)hdr + sheader->sh_offset);
    }
    return NULL;
}



/**
 * @brief Get the symbol name from string table
 * 
 * @param hdr header name
 * @param idx index of the string
 * @return char* string pointer
 */
static char *get_symbol_name(Elf32_Ehdr *hdr, size_t idx) {
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
static int get_symbol_type(Elf32_Sym *sym, Elf32_Shdr *sheader, char *t) {
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
static int get_symbol(Elf32_Ehdr* hdr, Elf32_Sym *sym, t_symbol *symbol) {
    unsigned int value;
    char *name;
    char t;
    Elf32_Shdr *sheader;


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



/**
 * @brief iterate over symbol table of 32 bit object file
 *  and populate the symbols array in file struct
 * 
 * @param hdr elf header
 * @param file 
 */
void iterate_over_32_symtab(Elf32_Ehdr *hdr, t_object_file *file) {
    Elf32_Shdr *sheader;
    Elf32_Sym *section;
    size_t idx;
    t_symbol *symbols;

    int i;

    
    section = NULL;
    sheader = get_sheader_by_name(hdr, ".symtab");
    section = (Elf32_Sym *)get_section_by_name(hdr, ".symtab");

    unsigned int size = (sheader->sh_size) / (sheader->sh_entsize);
    
    symbols = (t_symbol *)malloc(size * sizeof(t_symbol));
    i = 0;

    if (sheader && section) {
        idx = 0;
        while (idx < size) {
            if (idx != STN_UNDEF) {
                if (get_symbol(hdr, section, symbols) == 0) {
                    i++;
                    symbols++;
                }
            }
            idx++;
            section++;
        }
    }
    file->symbols = symbols - i;
    file->sym_num = i;
}
