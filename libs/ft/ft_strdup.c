#include <stdlib.h>


size_t ft_strlen(const char *);


char *ft_strdup(const char *lhs) {
    size_t size;
    char *rhs;
    int i;


    size = ft_strlen(lhs);
    rhs = (char *)malloc(size + 1);
    if (!rhs) {
        return rhs;
    }
    i = 0;
    while(lhs[i]) {
        rhs[i] = lhs[i];
        i++;
    }
    rhs[i] = '\0';
    return (rhs);
}