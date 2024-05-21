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


int to_print_value(t_symbol *sym) {
    if (sym->type == 'U' || sym->type == 'u' || sym->type == 'w') {
        return 0;
    }
    return 1;
}



void print_symbol_32(t_symbol *sym) {
    char buf[HEXREPSIZE + 1] = {0};
    char c;

    c = (to_print_value(sym))? '0': ' ';
    hexa_rep(sym->value, HEXREPSIZE, c, buf);

    output(buf);
    output(" ");
    soutput(&(sym->type), 1);
    output(" ");
    output(sym->name);
    output("\n");
}



void print_symbol_64(t_symbol *sym) {
    char buf[16 + 1] = {0};
    char c;

    c = (to_print_value(sym))? '0': ' ';
    hexa_rep(sym->value, 16, c, buf);

    output(buf);
    output(" ");
    soutput(&(sym->type), 1);
    output(" ");
    output(sym->name);
    output("\n");
}

void print_error(const char *str, const char *reason) {
    error("nm: ");
    error(str);
    error(": ");
    error(reason);
    error("\n");
}
