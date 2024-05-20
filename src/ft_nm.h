#ifndef __FT_NM_H__
#define __FT_NM_H__

#include <stdlib.h>
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


typedef enum s_check {
    VALID   = 0,
    NOIDENT = 1 << 0x0,
    NOCLASS = 1 << 0x1,
    NOENCOD = 1 << 0x2,
    NOVERS  = 1 << 0x3,
    NOVALID = 1 << 0x4,
} t_check;




void init_file(t_object_file *file);
int ft_nm(t_object_file *);
void print_error(const char *, const char*);
int map(t_object_file *file);
int load_elf_header(t_object_file *file);


// t_symbol functions
void    init_symbol_array(t_object_file *, size_t);
t_symbol *get_next_empty_symbol(t_object_file *file);

// printing
void print_symbol_32(t_symbol *);
void print_symbol_64(t_symbol *);


//checks
int check_header(const void *);
int get_class(const void *);
int check_32_format(const void *, int);
int check_64_format(const void *, int);

// 32bit object
void iterate_over_32_symtab(Elf32_Ehdr *, t_object_file *);

// 64 bit object
void iterate_over_64_symtab(const Elf64_Ehdr *, t_object_file *const);

#endif