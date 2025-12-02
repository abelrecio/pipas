NAME = pipex
BONUS_NAME = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MANDATORY_DIR = src_mandatory
MANDATORY_SRCS = $(MANDATORY_DIR)/main.c \
                 $(MANDATORY_DIR)/command_exec.c \
                 $(MANDATORY_DIR)/command_path.c \
                 $(MANDATORY_DIR)/file.c \
                 $(MANDATORY_DIR)/utils.c \
                 $(MANDATORY_DIR)/process.c
MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)

BONUS_DIR = src_bonus
BONUS_SRCS = $(BONUS_DIR)/bonus.c \
             $(MANDATORY_DIR)/command_exec.c \
             $(MANDATORY_DIR)/command_path.c \
             $(MANDATORY_DIR)/file.c \
             $(MANDATORY_DIR)/utils.c \
             $(MANDATORY_DIR)/process.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MANDATORY_OBJS)
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) $(LIBFT) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)
	@cp $(BONUS_NAME) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
