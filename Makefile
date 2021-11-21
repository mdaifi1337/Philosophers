NAME= philo
FLAGS= -Werror -Wall -Wextra
SRCS= ft_atoi.c main.c states.c tools.c shinigami.c
OBJS= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@gcc $(FLAGS) $(OBJS) -o $(NAME)
	@echo
	@echo "---------- \033[1;36mSuccessfully generated philo\033[0m ----------"
	@echo

%.o: %.c
	@echo Compiling : $< "\x1B[1;32m[OK]\x1B[0m"
	@gcc -g -c $< -o $@

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)
	@echo
	@echo "---------- \033[1;36mSuccessfully deleted philo\033[0m ----------"
	@echo

re: fclean all