NAME	= rush-02
SRCS	= rush-02.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

$(NAME):	${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:	${NAME}

re:	fclean all

clean:
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME}

.PHONY: all clean fclean re