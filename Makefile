CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin) #macOS
	CFLAGS += -I/opt/homebrew/opt/readline/include
	LDFLAGS = -L/opt/homebrew/opt/readline/lib
endif

SRC = src/signals/signals.c \
	src/signals/close_signals.c \
	src/execution/execution.c \
	src/execution/execution_utils.c \
	src/execution/execution_external.c \
	src/execution/execution_redirections.c \
	src/execution/pipeline.c \
	src/execution/consume_heredocs.c \
	src/parsing/parsing.c \
	src/parsing/lexer.c \
	src/parsing/parser.c \
	src/parsing/token_utils.c \
	src/parsing/command_utils.c \
	src/parsing/redirection_utils.c \
	src/parsing/parsing_utils.c \
	src/parsing/debug.c \
	src/parsing/expand_variables.c \
	src/reader.c \
	src/main.c \
	src/builtins/builtin_utils.c \
	src/builtins/builtin_echo.c \
	src/builtins/builtin_cd.c \
	src/builtins/builtin_pwd.c \
	src/builtins/builtin_export.c \
	src/builtins/builtin_unset.c \
	src/builtins/builtin_env.c \
	src/builtins/builtin_exit.c \
	src/parsing/lexer_utils.c \
	src/builtins/export_utils.c \
	src/execution/utils.c
	
HEADER = include/minishell.h

OBJ_DIR = obj
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)
NAME = minishell

all: $(NAME)

LIB_DIR = libft
LIBFT = $(LIB_DIR)/libft.a

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIB_DIR) -lft $(LDFLAGS) -lreadline -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/parsing
	mkdir -p $(OBJ_DIR)/signals
	mkdir -p $(OBJ_DIR)/builtins
	mkdir -p $(OBJ_DIR)/execution

$(LIBFT): force
	$(MAKE) -C $(LIB_DIR) bonus
	
force:

%.o: %.c $(HEADER) Makefile
	@mkdir -p $(dir $(OBJ_DIR)/$(@D))
	$(CC) $(CFLAGS) -c $< -o $(OBJ_DIR)/$@

# Ensure object directory exists before compiling any object, and create subdirs as needed
$(OBJ_DIR)/%.o: src/%.c $(HEADER) Makefile | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O3 -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIB_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

# AddressSanitizer/UBSan build
asan: CFLAGS += -g3 -fsanitize=address,undefined -fno-omit-frame-pointer
asan: re

# Valgrind interactive session
debug: CFLAGS += -g3
debug: re
	valgrind --leak-check=full \
		--track-origins=yes \
		--show-leak-kinds=all \
		--trace-children=yes \
		--suppressions=readline.supp \
		-s \
		./$(NAME)

# Batch leak checks
leaks: re
	bash tests/run_leak_checks.sh

.PHONY: all clean fclean re force debug asan leaks
