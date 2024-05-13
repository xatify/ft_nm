#ifndef __FT_NM_H__
#define __FT_NM_H__

#include "../libs/ft/libft.h"

typedef struct s_object_file {
    int fd;
    const char *name;
    int size;
    void *content;
} t_object_file;

int ft_nm(t_object_file *);

void print_error(const char *);

int map(t_object_file *file);

int load_elf_header(t_object_file *file);


#endif