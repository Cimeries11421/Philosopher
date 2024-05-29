NAME = libft.a

#------------------------------------------------#
#   Legend	                                     #
#------------------------------------------------#
# SRC_DIR   source directory
# OBJ_DIR   object directory
# SRCS      source files
# OBJS      object files
#
# CC        compiler
# CFLAGS    compiler flags


CFLAGS 	= -Wall -Wextra -Werror
CC 		= cc
SRC_DIR = ./src
OBJ_DIR = ./obj
SRCS= \
ft_atoi.c ft_isascii.c ft_memchr.c ft_printf.c ft_putnbr.c ft_strchr.c ft_strlcpy.c ft_strrchr.c \
ft_uns_putnbr.c putnbr_hex.c ft_bzero.c ft_isdigit.c ft_memcmp.c ft_print_ptr.c ft_putnbr_fd.c \
ft_strdup.c ft_strlen.c ft_strtrim.c get_next_line_bonus.c ft_calloc.c ft_isprint.c ft_memcpy.c \
ft_putchar.c ft_putstr.c ft_striteri.c ft_strmapi.c ft_substr.c ft_isalnum.c \
ft_itoa.c ft_memmove.c ft_putchar_fd.c ft_putstr_fd.c ft_strjoin.c ft_strncmp.c ft_tolower.c \
get_next_line_utils_bonus.c ft_isalpha.c ft_memset.c ft_putendl_fd.c ft_split.c\
ft_strlcat.c ft_strnstr.c ft_toupper.c get_next_line_utils.c ft_strtol.c


SRCS:= $(SRCS:%=$(SRC_DIR)/%)
OBJS:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DIR_DUP= mkdir -p $(@D) #Duplicate directory tree

#OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	ar -rc $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c src/libft.h src/ft_printf.h src/get_next_line_bonus.h \
	src/get_next_line.h
	$(DIR_DUP)
	$(CC) $(CFLAGS) -o $@ -c $<

#%.o : %.c 
#	$(CC) $(CFLAGS) -o $@ -c $<

re: fclean all

fclean: clean
	rm -f $(NAME)

clean :
	rm -rf $(OBJ_DIR)


.PHONY: all clean fclean re
