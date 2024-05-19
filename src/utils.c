#include "ft_nm.h"

#include <stdio.h>

void print_error(const char *str, const char *reason) {
    ERROR("nm: ");
    ERROR(str);
    ERROR(": ");
    ERROR(reason);
    ERROR("\n");
}
