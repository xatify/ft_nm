#include "ft_nm.h"

#include <stdio.h>




void init_symbol_array(t_object_file *file, size_t size) {
    file->symbols = (t_symbol *)malloc(size *sizeof(t_symbol));
    file->sym_num = 0;
}

t_symbol *get_next_empty_symbol(t_object_file *file) {
    return file->symbols + file->sym_num;
}

