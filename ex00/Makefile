# Your source code will be compiled as follows:
# make fclean
# make
# Executable name: rush-02
NAME	= rush-02
SRCS	= rush_02.c string.c string2.c read_dict.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc
# CFLAGS	= -Wall -Wextra -Werror

$(NAME):	${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:	${NAME}

re:	fclean all

clean:
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME}

.PHONY: all clean fclean re