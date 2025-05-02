NAME = turbo_pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
SRC = turbo_pipex.c turbo_pipex_utils.c
DEPS = turbo_pipex.h
ODIR = obj/
OBJ = $(SRC:%.c=$(ODIR)%.o)
LIBFT_DIR = ../lizzardlib
LIBFT = $(LIBFT_DIR)/libft.a

.PHONY: all clean fclean re libft_comp

all: libft_comp $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	@echo "compiling turbo_pipex 💪😎 <- turbo_pipex"
	@$(CC) $(OBJ) $(LIBFT) -o $(NAME)

libft_comp :
	@$(MAKE) -s -C $(LIBFT_DIR)

$(ODIR)%.o: %.c Makefile $(DEPS) | $(ODIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(ODIR):
	@mkdir $(ODIR)

clean:
	@echo "clean all obj🔮"
	@rm -rf $(ODIR)
	@$(MAKE) -s -C ../lizzardlib clean

fclean: clean
	@echo "remove exe 🍄"
	@rm -rf $(NAME)
	@$(MAKE) -s -C ../lizzardlib fclean

re: fclean all
