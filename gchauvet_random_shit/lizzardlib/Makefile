NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC=ft_atoi.c ft_bzero.c \
	ft_calloc.c ft_isalnum.c \
	ft_isalpha.c ft_isdigit.c \
	ft_isprint.c ft_memcmp.c \
	ft_memcpy.c ft_memmove.c \
	ft_memset.c ft_strchr.c \
	ft_strdup.c ft_strlcat.c \
	ft_strlcpy.c ft_strlen.c \
	ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c \
	ft_substr.c ft_tolower.c \
	ft_toupper.c ft_putchar_fd.c \
	ft_putstr_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_isascii.c \
	ft_strnstr.c ft_memchr.c \
	ft_striteri.c ft_strmapi.c \
	ft_split.c ft_itoa.c \
	ft_strjoin.c get_next_line.c \
	get_next_line_utils.c ft_printf.c \
	ft_printf_nbr.c ft_printf_str.c
BNS=ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c ft_lstdelone_bonus.c\
	ft_lstclear_bonus.c ft_lstiter_bonus.c \
	ft_lstmap_bonus.c
DEPS = libft.h
ODIR = obj/
OBJ = $(SRC:%.c=$(ODIR)%.o)

all: $(NAME)

$(NAME) : $(OBJ)
	@echo "compiling libft 📜 "
	@ar -rc $(NAME) $(OBJ)

$(ODIR)%.o: %.c Makefile libft.h | $(ODIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(ODIR):
	@mkdir $(ODIR)

bonus : 
	$(MAKE) SRC="$(SRC) $(BNS)"

clean:
	@rm -rf $(ODIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
