TARGET = src/nm


LIBFT_PATH = libs/ft

LIBFT = $(LIBFT_PATH)/libft.a

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

SRCS =	src/main.c		\
		src/ft_nm.c		\
		src/output.c	\
		src/checks.c	\
		src/check_header.c	\
		src/x86/section.c	\
		src/x86/sheader.c	\
		src/x86/shstrtab.c	\
		src/x86/symbol.c	\
		src/x86/x86.c		\
		src/x64/section.c	\
		src/x64/sheader.c	\
		src/x64/shstrtab.c	\
		src/x64/symbol.c	\
		src/x64/x64.c		\
		src/object_file.c


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

re: fclean all

test:
	@if [ "$(ARCHI)" -eq "32" ]; then \
	echo "testing on 32bit object"; \
	bash tests/test_32.sh "32"; \
	fi

	@if [ "$(ARCHI)" -eq "64" ]; then \
	echo "testing on 64bit object"; \
	bash tests/test_32.sh "64"; \
	fi
