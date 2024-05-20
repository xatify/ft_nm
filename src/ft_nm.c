#include <elf.h>
#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#include "ft_nm.h"


#include <stdio.h>
#include <stdlib.h>

#include <string.h>


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


int cmpsym(const void *sym1, const void *sym2) {
    int diff;

    diff = ft_stralnumcmp(((t_symbol *)sym1)->name, ((t_symbol *)sym2)->name);
    if (diff == 0) {
        return ft_strcmp(((t_symbol *)sym1)->name, ((t_symbol *)sym2)->name);
    }
    return diff;
}


int load_elf_header(t_object_file *file) {


    size_t size = EI_NIDENT;

    if (file->size <= (int)size) {
        return (-1);
    }

    int ret = check_header(file->content);
    if (ret != VALID) {

        print_error(file->name, "file format not recognized");
        return 1;
    }

    if (get_class(file->content) == ELFCLASS32) {
        if (check_32_format(file->content, file->size) == VALID) {
            iterate_over_32_symtab((Elf32_Ehdr *)file->content, file);
        }
        else {
            print_error(file->name, "file format not recognized");
            return 1;
        }
    }
    else if (get_class(file->content) == ELFCLASS64) {
        if (check_64_format(file->content, file->size) == VALID) {
            iterate_over_64_symtab((Elf64_Ehdr *)file->content, file);
        }
        else {
            print_error(file->name, "file format not recognized");
        }
    }


    ft_qsort(
        file->symbols, file->sym_num, sizeof(t_symbol), cmpsym
    );

    for (int i = 0; i < file->sym_num; i++) {
        if (get_class(file->content) == ELFCLASS32)
            print_symbol_32(file->symbols + i);
        else if (get_class(file->content) == ELFCLASS64)
            print_symbol_64(file->symbols + i);
    }

    // printf("%d\n", file->sym_num);

    return 0;
}