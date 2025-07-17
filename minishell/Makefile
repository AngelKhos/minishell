NAME=minishell
# /////////////////////////

CC=cc
CC_FLAGS=-Wall -Wextra -Werror -g3

# /////////////////////////

DIR_OBJS=.objs
DIR_DEPS=.deps

# /////////////////////////

SRCS=core/debug_tmp.c core/main.c core/free.c core/signal.c \
	builtins/env.c builtins/cd.c builtins/pwd.c builtins/echo.c builtins/exit.c \
	pars/ms_split.c pars/pars.c pars/tree_handle.c pars/tree_utils.c pars/here_doc.c \
	exec/exec.c exec/exec_builtins.c exec/exec_utils.c exec/redir_utils.c exec/exec_utils_2.c 

LIB= libft/libft.a
INCS= include/data.h include/env.h
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

$(DIR_OBJS):if (data->nb_pipes > 0)
		{
			if (prev_pipe[0] != -1)
			{
				close(prev_pipe[0]);
				close(prev_pipe[1]);
			}
			if (curr_pipe[0] != -1)
			{
				close(curr_pipe[0]);
				close(curr_pipe[1]);
			}
		}
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