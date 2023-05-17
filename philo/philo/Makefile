NAME=philo
CC=cc
CFLAGS= -Wall -Wextra -Werror #-fsanitize=thread
FILE=	outils1.c	\
outils2.c	\
workshop.c	\

FILO=$(FILE:.c=.o)

all: $(NAME)

$(NAME): $(FILO)
	$(CC) $(CFLAGS) $(FILO) -o $(NAME)

clean:
	rm -rf $(FILO)
fclean: clean
	rm -rf $(NAME)
re: fclean all