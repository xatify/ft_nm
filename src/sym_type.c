
#include <elf.h>
#include "ft_nm.h"

#define NONPRINT_TYPE   '\0'

#define LOWER_CASE(c) (c + 32)


#define BSS 0
#define RODATA 1

static const char* SECTIONS[] = {
    ".bss",
    ".rodata",
};



char *section_name_by_idx(Elf32_Ehdr *, int);

int is_local(Elf32_Sym *sym) {
    return (ELF32_ST_BIND(sym->st_info) == STB_LOCAL);
}

int is_global(Elf32_Sym *sym) {
    return (ELF32_ST_BIND(sym->st_info) == STB_GLOBAL);
}

int is_weak(Elf32_Sym *sym) {
    return (ELF32_ST_BIND(sym->st_info) == STB_WEAK);
}

int is_absolute(Elf32_Sym * sym) {
    return (sym->st_value == SHN_ABS);
}

int is_file_name(Elf32_Sym *sym) {
    return (ELF32_ST_TYPE(sym->st_info) == STT_FILE);
}

int is_text(Elf32_Sym *sym) {
    return (ELF32_ST_TYPE(sym->st_info) == STT_FUNC);
}

int is_object(Elf32_Sym *sym) {
    return (ELF32_ST_TYPE(sym->st_info) == STT_OBJECT);
}

int is_undefined(Elf32_Sym *sym) {
    return (sym->st_shndx == SHN_UNDEF);
}


char sym_type(Elf32_Ehdr* hdr, Elf32_Sym *sym) {
    char *sname;
    char type;

    type = NONPRINT_TYPE;
    if (is_absolute(sym))
        return ('A');
    if (is_file_name(sym)) {
        return NONPRINT_TYPE;
    }
    if (is_text(sym)) {
        type = 'T';
    }
    if (is_object(sym)) {
        type = 'D';
        sname = section_name_by_idx(hdr, sym->st_shndx);
        if (STREQUAL(SECTIONS[BSS], sname)) {
            type = 'B';
        }
        if (STREQUAL(SECTIONS[RODATA], sname)) {
            type = 'R';
        }

    }
    if (is_weak(sym)) {
        type = 'V';
    }

    if (is_undefined(sym)) {
        type = 'U';
    }

    if (type != NONPRINT_TYPE) {
        if (is_local(sym))
            return (LOWER_CASE(type));
    }
    return type;
}
