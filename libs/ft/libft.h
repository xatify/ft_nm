#ifndef __LIBFT_H__
#define __LIBFT_H__

#include <stddef.h>

typedef int(*t_comparator)(const void *, const void *);

size_t      ft_strlen(const char *);
char        *ft_strdup(const char *);

void        fd_write(const char* , int);

void        fd_swrite(const char *, int, size_t);

void        *ft_memcpy(void*, const void*, size_t);

void        *ft_memset(void*, int, size_t n);

void        *ft_bzero(void*, size_t);

int         ft_memcmp(const void*, const void*, size_t);

void        ft_qsort(void *base, int nmemb, int size, t_comparator);

int         ft_strcmp(const char *, const char *);

int         ft_stralnumcmp(const char *, const char *);


#define STREQUAL(s1,s2) !ft_memcmp(s1,s2,ft_strlen(s1))

#define STDOUT 1
#define STDERR 2

#define ERROR(s) fd_write(s, STDERR)
#define OUTPUT(s) fd_write(s, STDOUT)
#define SOUTPUT(s,l)  fd_swrite(s, STDOUT, l)

#endif