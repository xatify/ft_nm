#ifndef __FT_NM_H__
#define __FT_NM_H__

#include "../libs/ft/libft.h"
#include <elf.h>

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




// symbol types
int is_local(Elf32_Sym *);
int is_global(Elf32_Sym *);
int is_weak(Elf32_Sym *);
int is_absolute(Elf32_Sym *);
int is_file_name(Elf32_Sym *);
int is_text(Elf32_Sym *);
int is_object(Elf32_Sym *);
char sym_type(Elf32_Ehdr*,  Elf32_Sym*);


#endif