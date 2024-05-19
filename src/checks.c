#include "ft_nm.h"

#include <stdio.h>


static int check_ident(const void *file) {
    const unsigned char ident[] = {
        ELFMAG0,
        ELFMAG1,
        ELFMAG2,
        ELFMAG3,
    };
    const unsigned char *f;

    f = (const unsigned char *)file;

    if (ft_memcmp(f, ident, sizeof(ident))) {
        return NOIDENT;
    }
    return VALID;
}

static int check_class(const void *file) {
    const unsigned char *f;

    f = (const unsigned char *)file;

    if (
        f[EI_CLASS] != ELFCLASS32 &&
        f[EI_CLASS] != ELFCLASS64
    ) {
        return NOCLASS;
    }
    return VALID;
}

static int check_encoding(const void *file) {
    const unsigned char *f;

    f = (const unsigned char *)file;

    if (
        f[EI_DATA] != ELFDATA2LSB
    ) {
        return NOENCOD;
    }
    return VALID;
}

int check_header(const void *file) {
    return (
        check_ident(file) |
        check_class(file) |
        check_encoding(file)
    );
}


int get_class(const void *file) {
    const unsigned char *f;

    f = (const unsigned char *)file;

    return (f[EI_CLASS]);
}


int check_32_format(const void *file, int size) {
    Elf32_Ehdr *hdr;

    if (size <= (int)sizeof(Elf32_Ehdr)) {
        return 1;
    }

    hdr = (Elf32_Ehdr *)file;
    if (
        hdr->e_phoff >= (unsigned int)size ||
        hdr->e_shoff >= (unsigned int)size
    ) {
        return NOVALID;
    }

    return VALID;
}


