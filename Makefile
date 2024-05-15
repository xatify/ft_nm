TARGET = src/ft_nm


LIBFT_PATH = libs/ft

LIBFT = $(LIBFT_PATH)/libft.a

CC = gcc
CFALGS = --Wall -Wextra -Werror

SRCS =	src/main.c		\
		src/ft_nm.c		\
		src/utils.c		\
		src/sym_type.c




OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(TARGET): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(TARGET)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -rf $(TARGET)
	make -C $(LIBFT_PATH) fclean