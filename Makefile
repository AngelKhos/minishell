NAME=minishell
# /////////////////////////

CC=cc
CC_FLAGS=-Wall -Wextra -Werror -g3 #-fsanitize=address,leak

# /////////////////////////

DIR_OBJS=.objs
DIR_DEPS=.deps

# /////////////////////////

SRCS=core/debug_tmp.c core/utils.c core/main.c core/free.c core/global_free.c core/signal.c  \
	builtins/export.c builtins/env.c builtins/cd.c builtins/pwd.c builtins/echo.c builtins/exit.c builtins/unset.c \
	pars/ms_split.c pars/pars.c pars/pars_utils_2.c pars/pars_utils.c pars/redir_core.c pars/redir_infile.c pars/redir_outfile.c pars/here_doc.c pars/expand.c\
	env/tree_utils.c env/tree_utils_2.c  env/tree_handle.c env/init_default_env.c \
	exec/exec.c exec/exec_builtins.c exec/exec_utils.c exec/redir_utils.c exec/exec_utils_2.c 

LIB= libft/libft.a
INCS= include/data.h include/env.h
OBJS=$(SRCS:%.c=$(DIR_OBJS)/%.o)
DEPS=$(SRCS:%.c=$(DIR_DEPS)/%.d)

# /////////////////////////

all: compile_start libft $(NAME) compile_done

compile_start:
	echo "$(GREEN)Compile start... $(END)"

compile_done:
	echo "$(GREEN)Compiling done $(END)"

libft:
	$(MAKE) --silent -C ./libft

$(NAME): $(OBJS) $(DEPS) $(INCS) Makefile $(LIB)
	$(CC) $(CC_FLAGS) $(OBJS) $(LIB) -lreadline -o $@
	echo "$(BLUE)Your minishell is ready $(END)"


$(DIR_OBJS)/%.o: %.c Makefile 
	mkdir -p $(dir $@) $(DIR_DEPS)/$(dir $*)
	$(CC) $(CC_FLAGS) -MMD -MP -MF $(DIR_DEPS)/$*.d -c -o $@ $<

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