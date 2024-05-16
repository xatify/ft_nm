#ifndef __LIBFT_H__
#define __LIBFT_H__

#include <stddef.h>


size_t      ft_strlen(const char *);
char        *ft_strdup(const char *);

void        fd_write(const char* , int);

void        *ft_memcpy(void*, const void*, size_t);

void        *ft_memset(void*, int, size_t n);

void        *ft_bzero(void*, size_t);

int         ft_memcmp(const void*, const void*, size_t);

void        ft_qsort(void *base, int nmemb, int size, int (*)(const void*, const void*));

int         ft_strcmp(const char *, const char *);


#define STREQUAL(s1,s2) !ft_memcmp(s1,s2,ft_strlen(s1))

#define STDERR 2
#define ERROR(s) fd_write(s, STDERR)

#endif