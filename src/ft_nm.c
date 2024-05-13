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

int load_elf_header(t_object_file *file) {
    Elf32_Ehdr elf_header;

    // must initialise e_ident first
    // then check e_ident[EI_CLASS]
    // if it's 1 load 32 elf header
    // else if it's 2 load 64 elf header
    size_t size = sizeof(Elf32_Ehdr);

    if (size < file->size) {
        return (-1);
    }

    ft_bzero(&elf_header, sizeof(Elf32_Ehdr));
    ft_memcpy((void *)(&elf_header), file->content, sizeof(Elf32_Ehdr));


    return 0;
}