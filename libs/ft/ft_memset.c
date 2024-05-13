#include <stddef.h>

void *ft_memset(void *s, int c, size_t n) {
    unsigned char   *_s;
    unsigned char   _c;
    size_t          i;

    _s = (unsigned char *)s;
    _c = (unsigned char)c;

    i = 0;
    while(i < n) {
        *_s++ = _c;
        i++;
    }
    return s;
}
