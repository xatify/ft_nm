
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

static int ft_isalpha(int c) {
    return (ISLOWER(c) || ISUPPER(c));
}

static int ft_isdigit(int c) {
    return (c >= '0' && c <= '9');
}

static int ft_isalnum(int c) {
    return (ft_isalpha(c) || ft_isdigit(c));
}

int ft_stralnumcmp(const char *_s1, const char *_s2) {
    while (*_s1 && *_s2) {
        if (ft_isalnum(*_s1) && ft_isalnum(*_s2)) {
            if (*_s1 != *_s2)
                break;
            _s1++;
            _s2++;
        }
        if (*_s1 && !ft_isalnum(*_s1)) {
            _s1++;
        }
        if (*_s2 && !ft_isalnum(*_s2)) {
            _s2++;
        }

    }
    return (TOLOWER(*_s1) - TOLOWER(*_s2));
}
