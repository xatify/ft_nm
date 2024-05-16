
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

int ft_isalpha(int c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int ft_isdigit(int c) {
    return (c >= '0' && c <= '9');
}

int ft_isalnum(int c) {
    return (ft_isalpha(c) || ft_isdigit(c));
}


// int ft_stralnumcmp(const char *_s1, const char *_s2) {
//     while (*_s1 || *_s2) {
//         if (ft_isalnum(*_))
//     }
// }