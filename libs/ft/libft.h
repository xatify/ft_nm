#ifndef __LIBFT_H__
#define __LIBFT_H__

#include <stddef.h>


size_t      ft_strlen(const char *);
char        *ft_strdup(const char *);

void        fd_write(const char* , int);



#define STDERR 2
#define ERROR(s) fd_write(s, STDERR)

#endif