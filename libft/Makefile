NAME=libft.a
CC=cc
AR=ar 
AR_ARG=-rcs
CC_FLAGS=-Wall -Wextra -Werror
SRCS=ft_atoi.c\
	ft_isalpha.c\
	ft_strmapi.c\
	ft_putnbr_fd.c\
	ft_putendl_fd.c\
	ft_putstr_fd.c\
	ft_putchar_fd.c\
	ft_striteri.c\
	ft_strtrim.c\
	ft_substr.c\
	ft_itoa.c\
	ft_strlcat.c\
	ft_strdup.c\
	ft_calloc.c\
	ft_strnstr.c\
	ft_memcmp.c\
	ft_memchr.c\
	ft_strncmp.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_isprint.c\
	ft_isspace.c\
	ft_memset.c\
	ft_strlcpy.c\
	ft_strndup.c\
	ft_toupper.c\
	ft_bzero.c\
	ft_isascii.c\
	ft_memcpy.c\
	ft_split.c\
	ft_strlen.c\
	ft_isalnum.c\
	ft_isdigit.c\
	ft_memmove.c\
	ft_strjoin.c\
	ft_tolower.c\
	ft_lstnew_bonus.c\
	ft_lstadd_front_bonus.c\
	ft_lstsize_bonus.c\
	ft_lstlast_bonus.c\
	ft_lstadd_back_bonus.c\
	ft_lstdelone_bonus.c\
	ft_lstclear_bonus.c\
	ft_lstiter_bonus.c\
	ft_lstmap_bonus.c\
	ft_printf.c\
	ft_printhexa.c\
	ft_printnbr.c\
	ft_printstr.c\
	ft_utils.c\
	get_next_line.c\
	get_next_line_utils.c
OBJS=$(SRCS:%.c=$(DIR_OBJS)/%.o)
DEPS=$(SRCS:%.c=$(DIR_DEPS)/%.o)

DIR_OBJS=.objs
DIR_DEPS=.deps

all: $(NAME)

$(NAME): $(OBJS) Makefile
	echo "$(GREEN) Compiling libft ... $(END)" 
	$(AR) $(AR_ARG) $@ $(OBJS)
	
$(DIR_OBJS)/%.o: %.c Makefile libft.h | $(DIR_OBJS) $(DIR_DEPS)
	$(CC) $(CC_FLAGS) -MMD -MP -MF $(DIR_DEPS)/$*.d -c -o $@ $<

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

$(DIR_DEPS):
	mkdir -p $(DIR_DEPS)

clean:
	rm -rf $(DIR_OBJS)
	rm -rf $(DIR_DEPS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SILENT:


GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
END=\033[0m