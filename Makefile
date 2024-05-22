TARGET = src/ft_nm


LIBFT_PATH = libs/ft
SRC_DIR = src

LIBFT = $(LIBFT_PATH)/libft.a

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

SRCS =	$(SRC_DIR)/main.c			\
		$(SRC_DIR)/ft_nm.c			\
		$(SRC_DIR)/output.c			\
		$(SRC_DIR)/checks.c			\
		$(SRC_DIR)/utils.c			\
		$(SRC_DIR)/check_header.c	\
		$(SRC_DIR)/x86/section.c	\
		$(SRC_DIR)/x86/sheader.c	\
		$(SRC_DIR)/x86/shstrtab.c	\
		$(SRC_DIR)/x86/symbol.c		\
		$(SRC_DIR)/x86/x86.c		\
		$(SRC_DIR)/x64/section.c	\
		$(SRC_DIR)/x64/sheader.c	\
		$(SRC_DIR)/x64/shstrtab.c	\
		$(SRC_DIR)/x64/symbol.c		\
		$(SRC_DIR)/x64/x64.c		\
		$(SRC_DIR)/object_file.c	\
		$(SRC_DIR)/symbol.c


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

norm:
	norminette $(LIBFT_PATH)
	norminette $(SRC_DIR)