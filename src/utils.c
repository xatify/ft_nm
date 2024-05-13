#include "ft_nm.h"

#include <stdio.h>

void print_error(const char *str) {
    ERROR("nm : '");
    ERROR(str);
    ERROR("' : ");
    perror(NULL);
}
