#include <stddef.h>
#include "ft_nm.h"


#define HEXREPSIZE 8

#define HEXADIGIT(n) (n < 10)? '0' + n: 'a' + (n - 10)

static inline void fill(char *buf, char c, size_t size) {
    while(size--) *buf++ = c;
}

void hexa_rep(size_t n, int size, char c, char *buf) {

    while(size--) *buf++ = c;
    while (n) {
        *--buf = HEXADIGIT(n % 16);
        n = n / 16;
    }
}


static int to_print_value(t_symbol *sym) {
    if (sym->type == 'U' || sym->type == 'u' || sym->type == 'w' || sym->type == 'W') {
        return 0;
    }
    return 1;
}



void print_symbol(t_symbol *sym) {
    char buf[HEXREPSIZE + 1] = {0};
    char c;

    c = (to_print_value(sym))? '0': ' ';
    hexa_rep(sym->value, HEXREPSIZE, c, buf);

    OUTPUT(buf);
    OUTPUT(" ");
    SOUTPUT(&(sym->type), 1);
    OUTPUT(" ");
    OUTPUT(sym->name);
    OUTPUT("\n");
}


