FLAGS = -Wall -Werror -Wextra -fsanitize=thread -g
HEADER = philo.h
CC = cc
NAME = philo

SRC = 	debug_helper.c main.c parse_input.c init_data.c free_data.c feast.c \
		feast_utils.c viking_eat.c sleep_think.c ragnar.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -fsanitize=thread -g $^ -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJ)

re: fclean all

.PHONY: clean

# test: h t a
# 	@echo $^

# h:
# t:
# a:`