NAME=minishell
# /////////////////////////

CC=cc
CC_FLAGS=-Wall -Wextra -Werror -g3

# /////////////////////////

DIR_OBJS=.objs
DIR_DEPS=.deps

# /////////////////////////

SRCS= core/main.c core/free.c builtins/env.c builtins/cd.c builtins/pwd.c builtins/exit.c exec/exec.c exec/exec_utils.c exec/exec_builtins.c pars/fake_parsing.c pars/tree_handle.c

LIB= libft/libft.a
INCS= include/data.h
OBJS=$(SRCS:srcs/%.c=$(DIR_OBJS)/%.o)
DEPS=$(SRCS:srcs/%.c=$(DIR_DEPS)/%.d)

# /////////////////////////

all: compile_start libft $(NAME) compile_done

compile_start:
	echo "$(GREEN) Compile start ... $(END)"

compile_done:
	echo "$(GREEN) Compiling done $(END)"

libft:
	$(MAKE) --silent -C ./libft

$(NAME): $(OBJS) $(DEPS) $(INCS)
	$(CC) $(CC_FLAGS) $(OBJS) $(LIB) -lreadline -o $@
	echo "$(BLUE) Your minishell is ready $(END)"


$(DIR_OBJS)/%.o: srcs/%.c Makefile | $(DIR_OBJS) $(DIR_DEPS) 
	$(CC) $(CC_FLAGS) -MMD -MP -MF $(DIR_DEPS)/$*.d -c -o $@ $<

# /////////////////////////

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

$(DIR_DEPS):
	mkdir -p $(DIR_DEPS)

# /////////////////////////

clean:
	echo "$(RED)Removing files... $(END)"
	$(MAKE) --silent -C  ./libft fclean
	rm -rf $(DIR_OBJS)
	rm -rf $(DIR_DEPS)

fclean: clean
	echo "$(RED)Removing executable... $(END)"
	$(MAKE) --silent -C  ./libft fclean
	rm -rf $(NAME)

re: fclean all

# /////////////////////////

GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
END=\033[0m

# /////////////////////////

.PHONY: all clean fclean re libft
.SILENT: