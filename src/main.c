#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#include "../libs/ft/libft.h"
#include "ft_nm.h"

int open_file(t_object_file* file, const char *name) {
    int fd;
    fd = open(name, O_RDONLY);
    if (fd < 0) {
        print_error(name);
        return -1;
    }
    file->fd = fd;
    file->name = name;
    return 0;
}



int ft_nm(t_object_file *file) {
    int ret = map(file);

    // printf("maping %d\n", ret);
    if (ret == 0) {
        load_elf_header(file);

    }
    else {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    t_object_file file;
    int ret;
    int error;
    int i;

    file.fd = -1;
    file.name = NULL;

    error = 0;
    if (argc == 1) {
        ret = open_file(&file, "a.out");
        if (ret == -1) {
            exit (1);
        }
        ret = ft_nm(&file);
        if (ret) {
            error = 1;
        }
        
    }
    else {
        i = 1;
        while (i < argc) {
            close(file.fd);
            file.fd = -1;
            ret = open_file(&file, argv[i]);
            if (ret == -1) {
                exit(1);
            }
            ret = ft_nm(&file);
            if (ret) {
                error = 1;
            }
            i++;
        }
    }
    if (error) return 1;
    return (0);
}


