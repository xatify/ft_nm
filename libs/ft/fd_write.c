#include <unistd.h>

size_t ft_strlen(const char *);

void fd_write(const char *str, int fd) {
    write(fd, str, ft_strlen(str));
}
