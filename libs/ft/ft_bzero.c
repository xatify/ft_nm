#include "libft.h"


void *ft_memset(void *, int, size_t);

void *ft_bzero(void *s, size_t n) {
    return ft_memset(s, 0, n);
}