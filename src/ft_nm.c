#include <elf.h>
#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#include "ft_nm.h"


#include <stdio.h>

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

Elf32_Shdr* symtab(Elf32_Ehdr *hdr) {
    Elf32_Shdr* sheader = elf_sheader(hdr);
    char *name;
    const char* symtab = ".symtab";
    int idx;


    idx = 0;
    while (idx < hdr->e_shnum) {
        if (idx != SHN_UNDEF) {
            name = shstr_lookup_string(hdr, sheader->sh_name);
            if (!ft_memcmp(name, symtab, ft_strlen(symtab))) {
                printf("found symtab: %s\n", name);
                return sheader;
            }
        }
        idx++;
        sheader += 1;
    }
    return NULL;
}

// void iterate_over_section_names(Elf32_Ehdr *hdr) {
//     Elf32_Shdr* sheader = elf_sheader(hdr);

//     int i = 0;

//     // some section header table indexes are reserved,
//     // an object file will not have sections for these
//     // special indexes

//     printf("sections names:\n");
//     while(i < hdr->e_shnum) {
//         if (i != SHN_UNDEF) {
//             char *name = shstr_lookup_string(hdr, sheader->sh_name);
//             // printf("%s\n", name);

//         }
//         sheader += 1;
//         i++;
//     }
// }



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

    int is_elf = elf_check_file(&elf_header);

    // printf("is elf: %d\n", is_elf);

    // printf("class 32: %d\n", elf_class(&elf_header));

    // printf("little endian: %d\n", elf_byte_order(&elf_header));

    // _elf_machine(&elf_header);

    // _elf_type(&elf_header);

    // Elf32_Shdr* sheader = elf_sheader((Elf32_Ehdr *)file->content);

    // printf("section header offset: %d\n", elf_header.e_shoff);


    // iterate_over_section_names(&elf_header);

    // lookup_string((Elf32_Ehdr *)file->content, 0);

    // iterate_over_section_names((Elf32_Ehdr *)file->content);

    symtab((Elf32_Ehdr *)file->content);


    return 0;
}