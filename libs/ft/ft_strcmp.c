
#include "libft.h"

#include <stdlib.h>

int ft_strcmp(const char *_s1, const char *_s2) {

    unsigned char *s1 = (unsigned char *)_s1;
    unsigned char *s2 = (unsigned char *)_s2;
    while (*s1 == *s2) {
        if (*s1 == '\0') break;

        ++s1;
        ++s2;
    }
    return (*s1 - *s2);
}


#define ISLOWER(c) (c >= 'a' && c <= 'z')
#define ISUPPER(c) (c >= 'A' && c <= 'Z')
#define TOLOWER(c) (ISUPPER(c)? c + 0x20: c)
#define UNDERSCORE '_'

static int ft_isalpha(int c) {
    return (ISLOWER(c) || ISUPPER(c));
}

static int ft_isdigit(int c) {
    return (c >= '0' && c <= '9');
}

static int ft_isalnum(int c) {
    return (ft_isalpha(c) || ft_isdigit(c));
}


static void no_special(const char *_s1, char *s1) {
    int j;

    j = 0;
    for(size_t i = 0; i < ft_strlen(_s1); i++) {
        if (ft_isalnum(_s1[i])) {
            s1[j] = TOLOWER(_s1[i]);
            j++;
        }
    }
    s1[j] = '\0';
}


int ft_stralnumcmp(const char *_s1, const char *_s2) {
    char *s1, *s2;
    int ret;


    s1 = malloc(ft_strlen(_s1) + 1);
    no_special(_s1, s1);
    s2 = malloc(ft_strlen(_s2) + 1);
    no_special(_s2, s2);

    ret = ft_strcmp(s1, s2);
    free(s1);
    free(s2);
    return ret;
}
