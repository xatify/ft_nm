
TARGET = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS =	fd_write.c		\
		ft_strdup.c		\
		ft_strlen.c		\
		ft_memcpy.c		\
		ft_memset.c		\
		ft_bzero.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $(TARGET) $(OBJS)


.c.o:
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(TARGET)


