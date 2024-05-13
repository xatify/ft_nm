#ifndef __LIBFT_H__
#define __LIBFT_H__

#include <stddef.h>


size_t      ft_strlen(const char *);
char        *ft_strdup(const char *);

void        fd_write(const char* , int);

void        *ft_memcpy(void*, const void*, size_t);

void        *ft_memset(void*, int, size_t n);

void        *ft_bzero(void*, size_t);



#define STDERR 2
#define ERROR(s) fd_write(s, STDERR)

#endif