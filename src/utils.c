#include "ft_nm.h"

#include <stdio.h>

void print_error(const char *str) {
    ERROR("nm: '");
    ERROR(str);
    ERROR("': ");
    ERROR("No such file\n");
    // perror(NULL);
}
