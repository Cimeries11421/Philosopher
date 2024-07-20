NAME = philo
CFLAGS = -Wall -Wextra -Werror
INCFLAGS= -I include #-I./ # -I : include 
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
	src/destroy_mutex.c \
	src/ft_strtol.c \
	src/ft_isdigit.c

OBJ = $(SRC:.c=.o)

HEADERS = include/philo.h

all :
	$(MAKE) $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(INCFLAGS) $(OBJ) -o $(NAME) 

%.o : %.c $(HEADERS) 	
	$(CC) $(CFLAGS) $(INCFLAGS) -o $@ -c $<

re: fclean
	$(MAKE) all

fclean: clean
	rm -f $(NAME)

clean :
	rm -rf $(OBJ)

sanitize:
	make CFLAGS="-Wall -Wextra -g3 -fsanitize=thread"

debug:
	make CFLAGS="-Wall -Wextra -g3"

.PHONY : all clean fclean re
