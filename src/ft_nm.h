#ifndef __FT_NM_H__
#define __FT_NM_H__

#include "../libs/ft/libft.h"
#include <elf.h>

typedef struct s_symbol {
    size_t value;
    char type;
    char *name;
} t_symbol;

typedef struct s_object_file {
    int fd;
    char *name;
    int size;
    void *content;
    int sym_num;
    t_symbol *symbols;
} t_object_file;


void init_file(t_object_file *file);
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


// printing
void print_symbol(t_symbol *);

#endif