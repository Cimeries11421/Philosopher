NAME = philo
CFLAGS = -Wall -Wextra  #-Werror
INCFLAGS= -I libft/src -I include #-I./ # -I : include 
CC = cc
SRC = \
	src/main.c \
	src/parse_input_and_store_in_struct.c \
	src/create_philosopher_and_launch_their_routine.c \
	src/begin_routine.c \
	src/eating_sleeping_thinking.c \
	src/wait_for_task.c \
	src/check_philo_all_alive.c \
	src/get_time.c \
	src/print_time_and_state.c \
	src/destroy_mutex.c

OBJ = $(SRC:.c=.o)

LIBFT= libft/libft.a

HEADERS= include #/minishell.h libft/src/libft.h

all : lib
	$(MAKE) $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(INCFLAGS) $(OBJ) $(LIBFT) -o $(NAME) 

%.o : %.c $(HEADERS) 	
	$(CC) $(CFLAGS) $(INCFLAGS) -o $@ -c $<

lib :
	$(MAKE) -C libft/

re: fclean
	$(MAKE) all

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C libft/

clean :
	rm -rf $(OBJ)
	$(MAKE) clean -C libft/


sanitize:
	make CFLAGS="-Wall -Wextra -g3 -fsanitize=thread"

debug:
	make CFLAGS="-Wall -Wextra -g3"

.PHONY : all clean fclean re
