# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abrecio- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/25 18:37:02 by abrecio-          #+#    #+#              #
#    Updated: 2025/10/12 21:44:23 by abrecio-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Macros
NAME    = libft.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
AR      = ar rcs
RM      = rm -f

# Sources
SRCS    = ft_atoi.c \
	ft_calloc.c \
	ft_bzero.c \
	ft_isalnum.c \
	get_next_line/get_next_line_utils_bonus.c \
	get_next_line/get_next_line_bonus.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c

SRCS_B  = ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstmap_bonus.c \
	ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c\
	ft_lstsize_bonus.c

# Object files
OBJS    = $(SRCS:.c=.o)
OBJS_B  = $(SRCS_B:.c=.o)

# Phony targets
.PHONY: all bonus clean fclean re

# Default target: build library
all: $(NAME)

# Create or update library with main objects
$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

# Compile each .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Bonus: compile bonus objects and update library
bonus: $(NAME) $(OBJS_B)
	$(AR) $(NAME) $(OBJS_B)

# Remove object files
clean:
	$(RM) $(OBJS) $(OBJS_B)

# Remove object files and library
fclean: clean
	$(RM) $(NAME)

# Rebuild everything
re: fclean all


