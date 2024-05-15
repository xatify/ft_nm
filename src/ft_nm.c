#include <elf.h>
#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#include "ft_nm.h"


#include <stdio.h>
#include <stdlib.h>


int map(t_object_file *file) {
    struct stat filestat;

    if (fstat(file->fd, &filestat) == -1) {
        return (-1);
    }
    file->size = filestat.st_size;

    file->content = mmap(NULL, file->size, PROT_READ, MAP_PRIVATE, file->fd, 0);

    if (file->content == MAP_FAILED) {
        return (-1);
    }
    return 0;
}

int elf_check_file(Elf32_Ehdr *hdr) {
    const unsigned char ident[] = {
                    ELFMAG0,
                    ELFMAG1,
                    ELFMAG2,
                    ELFMAG3 };
    if (!hdr) {
        return 1;
    }

    if (ft_memcmp(hdr->e_ident, ident, sizeof(ident))) {
        return 1;
    }
    return 0;

}

int elf_class(Elf32_Ehdr *hdr) {
    if (
        // we will implement only 32 class for now
        hdr->e_ident[EI_CLASS] != ELFCLASS32
    )
        return 1;
    return 0;
}

int elf_byte_order(Elf32_Ehdr *hdr) {
    if (
        // support only 2LSB for now
        hdr->e_ident[EI_DATA] != ELFDATA2LSB
    )
        return 1;
    return 0;
}


void _elf_machine(Elf32_Ehdr *hdr) {
    printf("machine %d\n", hdr->e_machine);
}

void _elf_type(Elf32_Ehdr *hdr) {
    printf("type : %d\n", hdr->e_type);
}


Elf32_Shdr* elf_sheader(Elf32_Ehdr *hdr) {
    return (Elf32_Shdr *)((char *)hdr + hdr->e_shoff);
}

Elf32_Shdr* elf_sheader_idx(Elf32_Ehdr *hdr, int idx) {
    return elf_sheader(hdr) + idx;
}

Elf32_Shdr* shstrtab_header(Elf32_Ehdr *hdr) {
    if (hdr->e_shstrndx != SHN_UNDEF)
        return (elf_sheader_idx(hdr, hdr->e_shstrndx));
    return NULL;
}

char *shstr_lookup_string(Elf32_Ehdr *hdr, int offset) {
    Elf32_Shdr *sth = shstrtab_header(hdr);
    return (char *)hdr + sth->sh_offset + offset;
}

char *section_name_by_idx(Elf32_Ehdr *hdr, int idx) {
    Elf32_Shdr *sheader;

    sheader = elf_sheader_idx(hdr, idx);
    if (sheader) {
        return shstr_lookup_string(hdr, sheader->sh_name);
    }
    return NULL;
}


Elf32_Shdr *get_sheader_by_name(Elf32_Ehdr *hdr, const char* name) {
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

void *get_section_by_name(Elf32_Ehdr *hdr, const char *name) {
    Elf32_Shdr *sheader;

    sheader = get_sheader_by_name(hdr, name);
    if (sheader) {
        return ((char *)hdr + sheader->sh_offset);
    }
    return NULL;
}


// #define ELF32_ST_BIND(i) ((i)>>4)
// #define ELF32_ST_TYPE(i) ((i)&0xf)
// #define ELF32_ST_INFO(b, t) (((b)<<4) + ((t)&0xf))

char *get_symbol_name(Elf32_Ehdr *hdr, size_t idx) {
    char *symstrtab = get_section_by_name(hdr, ".strtab");

    if (symstrtab) {
        return symstrtab + idx;
    }
    return NULL;
}


int get_symbol(Elf32_Ehdr* hdr, Elf32_Sym *sym, t_symbol *symbol) {
    unsigned int value;
    char *name;
    char type;


    if (sym->st_name) {
        value = sym->st_value;
        name = get_symbol_name(hdr, sym->st_name);
        type = sym_type(hdr, sym);


        if (name && type) {
            symbol->name = name;
            symbol->value = value;
            symbol->type = type;
            return 0;
        }
    }
    return -1;
}




void iterate_over_symtab(Elf32_Ehdr *hdr, t_object_file *file) {
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
                // print_symbol(hdr, section);
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




int load_elf_header(t_object_file *file) {
    Elf32_Ehdr elf_header;

    // must initialise e_ident first
    // then check e_ident[EI_CLASS]
    // if it's 1 load 32 elf header
    // else if it's 2 load 64 elf header
    size_t size = sizeof(Elf32_Ehdr);

    if (file->size < size) {
        return (-1);
    }

    ft_bzero(&elf_header, sizeof(Elf32_Ehdr));
    ft_memcpy((void *)(&elf_header), file->content, sizeof(Elf32_Ehdr));


    iterate_over_symtab((Elf32_Ehdr *)file->content, file);

    for (int i=0; i < file->sym_num; i++) {
        printf("%s\n", file->symbols[i].name);
    }

    return 0;
}