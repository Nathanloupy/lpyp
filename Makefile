# Makefile for lpyp-1.0.0

NAME		= lpyp.a

SRC_DIR		= src

SRC_FILES	= lpyp.c
SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJS		= $(SRCS:.c=.o)

TEST_SRC_FILES = main.c
TEST_SRCS      = $(addprefix $(SRC_DIR)/, $(TEST_SRC_FILES))

GREEN		= \033[0;32m
BLUE		= \033[0;34m
YELLOW		= \033[0;33m
RED			= \033[0;31m
RESET		= \033[0m

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iinclude -Ilibft
AR			= ar
ARFLAGS		= rcs
RM			= rm -f

LIBFT		= libft/libft.a

all: $(NAME) ## Compile lpyp library and libft.

$(NAME): $(OBJS)
	@echo "$(BLUE)Compiling libft...$(RESET)"
	@make -s --no-print-directory -C libft
	@echo "$(GREEN)Creating archive $(NAME)...$(RESET)"
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)

%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

test: all ## Compile a test executable.
	@echo "$(BLUE)Compiling test executable...$(RESET)"
	@$(CC) $(CFLAGS) -o test_lpyp $(TEST_SRCS) $(NAME) $(LIBFT)

clean: ## Remove object files.
	@echo "$(RED)Cleaning object files...$(RESET)"
	@$(RM) $(OBJS)
	@make -s --no-print-directory -C libft clean

fclean: ## Remove all generated files.
	@echo "$(RED)Cleaning object files...$(RESET)"
	@$(RM) $(OBJS)
	@echo "$(RED)Cleaning library and executable...$(RESET)"
	@$(RM) $(NAME) test_lpyp
	@make -s --no-print-directory -C libft fclean

re: fclean all ## Re-compile the entire project.

help: ## Show this help message.
	@egrep -h '\s##\s' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m  %-30s\033[0m %s\n", $$1, $$2}'

.PHONY: all clean fclean re test help
