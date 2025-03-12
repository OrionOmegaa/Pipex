.SILENT:

#Flags

CFLAGS=-Wall -Wextra -Werror

#Files

FILES=	$(SRC_DIR)/pipex.c \
	$(SRC_DIR)/pipex_utils.c \

BONUS =	$(SRC_DIR)/pipex_bonus.c \
	$(SRC_DIR)/pipex_utils_bonus.c \

OBJS=$(FILES:.c=.o)

BOBJ=$(BONUS:.c=.o)

#Directories

SRC_DIR=src

#Includes

NAME=pipex
BONUS_NAME=pipex_bonus
LIBFT=./includes/libft/libft.a

#Decoration

CYAN = \033[1;36m
GREEN = \033[1;32m
RED = \033[1;31m
RESET = \033[0m
BOX_TOP = /===============\\
BOX_MID = |
BOX_MID_END = |
BOX_BOT = \\===============/

#Compilation

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(RED)Making Pipex ...$(RESET)"
	@cc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@touch infile
	@echo "$(GREEN)Pipex Done Succesfully !$(RESET)"
	@echo "$(CYAN)$(BOX_TOP) $(RESET)"
	@echo "$(CYAN)$(BOX_MID)$(RESET)$(GREEN)Executable Done$(RESET)$(CYAN)$(BOX_MID_END)$(RESET)"
	@echo "$(CYAN)$(BOX_BOT)$(RESET)"

$(BONUS_NAME): $(BOBJ) $(LIBFT)
	@echo "$(RED)Making Pipex ...$(RESET)"
	@cc $(CFLAGS) -o $(BONUS_NAME) $(BOBJ) $(LIBFT)
	@touch infile
	@echo "$(GREEN)Bonus Pipex Done Succesfully !$(RESET)"
	@echo "$(CYAN)$(BOX_TOP) $(RESET)"
	@echo "$(CYAN)$(BOX_MID)$(RESET)$(GREEN)Executable Done$(RESET)$(CYAN)$(BOX_MID_END)$(RESET)"
	@echo "$(CYAN)$(BOX_BOT)$(RESET)"

$(LIBFT):
	@make -C ./includes/libft --no-print-directory

%.o: %.c
	@gcc $(CFLAGS) -I includes -c $< -o $@ 

#Commands

all: $(NAME)

clean:
	@echo "$(RED)Cleaning object file in progress ...$(RESET)"
	@rm -f $(OBJS) $(BOBJ)
	@make clean -C ./includes/libft --no-print-directory
	@echo "$(GREEN)CLEAN Done Succesfully !$(RESET)"

fclean: clean
	@echo "$(RED)Full Clean in progress ...$(RESET)"
	@rm -f $(NAME) $(BOBJ) $(BONUS_NAME)
	@rm -f infile outfile
	@make fclean -C ./includes/libft --no-print-directory
	@echo "$(GREEN)FCLEAN Done Succesfully !$(RESET)"

re: fclean all

rebonus: fclean bonus

bonus: $(BONUS_NAME)

#phony

.PHONY: all clean fclean re bonus rebonus
