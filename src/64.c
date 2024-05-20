#include "ft_nm.h"

#include <stdio.h>


static Elf64_Shdr *elf64_sheader(const Elf64_Ehdr *hdr) {
    return (Elf64_Shdr *)((char *)hdr + hdr->e_shoff);
}


static Elf64_Shdr *elf64_sheader_idx(
    const Elf64_Ehdr *hdr,
    const size_t idx
) {
    return elf64_sheader(hdr) + idx;
}

static Elf64_Shdr* shstrtab_64header(const Elf64_Ehdr *hdr) {
    if (hdr->e_shstrndx != SHN_UNDEF) {
        return (elf64_sheader_idx(hdr, hdr->e_shstrndx));
    }
    return NULL;
}


static char *shstr64_lookup_string(
    const Elf64_Ehdr *hdr,
    const size_t offset
) {
    Elf64_Shdr *sth = shstrtab_64header(hdr);
    return (char *)hdr + sth->sh_offset + offset;
}


static Elf64_Shdr * symtab_sh(const Elf64_Ehdr *hdr) {
    Elf64_Shdr *sheader;

    sheader = elf64_sheader(hdr);
    for (size_t i = 0; i < hdr->e_shnum; i++) {
        if (i != SHN_UNDEF) {
            if (sheader->sh_type == SHT_SYMTAB) {
                return sheader;
            }
        }
        sheader++;
    }
    return NULL;
}


static Elf64_Shdr *get64_sheader_by_name(
    const Elf64_Ehdr *hdr,
    const char *name
) {
    Elf64_Shdr *sheader;
    char *_name;
    size_t idx;

    sheader = elf64_sheader(hdr);
    idx = 0;
    while (idx < hdr->e_shnum) {
        if (idx != SHN_UNDEF) {
            _name = shstr64_lookup_string(hdr, sheader->sh_name);
            if (!ft_memcmp(name, _name, ft_strlen(name))) {
                return sheader; 
            }
        }
        idx++;
        sheader++;
    }
    return NULL;
}

static void *get_64section_by_name(const Elf64_Ehdr *hdr, const char *name) {
    Elf64_Shdr *sheader;

    sheader = get64_sheader_by_name(hdr, name);
    if (sheader) {
        return ((char *)hdr + sheader->sh_offset);
    }
    return NULL;
}


static int get_64symbol_type(
    const Elf64_Sym *sym,
    const Elf64_Shdr *sheader,
    char *t
) {
    unsigned char bind;
    unsigned char type;

    bind = ELF64_ST_BIND(sym->st_info);
    type = ELF64_ST_TYPE(sym->st_info);
    
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


static int get_64symbol(
    const Elf64_Ehdr *hdr, 
    const Elf64_Sym *sym,
    t_object_file *file,
    const char *strtab
) {
    Elf64_Shdr *sheader;
    t_symbol *symbol;
    char *name;
    char t;

    symbol = get_next_empty_symbol(file);
    
    if (sym->st_name) {
        name = (char *)strtab + sym->st_name;
        sheader = elf64_sheader_idx(hdr, sym->st_shndx);
        if (get_64symbol_type(sym, sheader, &t)) {
            return -1;
        }

        if (*name && t) {
            symbol->name = name;
            symbol->value = sym->st_value;
            symbol->type = t;
            return 0;
        }
    }
    return -1;
}

void iterate_over_64_symtab(const Elf64_Ehdr* hdr, t_object_file * const file) {
    Elf64_Shdr *sheader;
    char *strtab;
    size_t idx;

    sheader = symtab_sh(hdr);
    init_symbol_array(file, sheader->sh_size / sheader->sh_entsize);
    strtab = (char *)get_64section_by_name(hdr, ".strtab");
    idx = 0;
    while (idx < (sheader->sh_size / sheader->sh_entsize)) {
        if (idx != STN_UNDEF) {
            if (get_64symbol(
                hdr,
                (Elf64_Sym *)((char *)hdr + sheader->sh_offset) + idx,
                file,
                strtab) == 0
            ) {
                file->sym_num += 1;
            }
        }
        idx++;
    }
}

