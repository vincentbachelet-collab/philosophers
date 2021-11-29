NAME		=	philo

SRC_FILES	=	src/main.c \

INCLUDE_PATH	=	include/

SRC_OBJS	=	$(SRC_FILES:.c=.o)

CC		=	clang

CFLAGS		=	-Wall -Wextra -Werror -I -g -fsanitize=address

RM		=	rm -rf

%.o : %.c
	@$(CC) -c $(CFLAGS) $< -o $@

all:			$(NAME)

$(NAME):		$(SRC_OBJS)
					@$(CC) $(CFLAGS) $(SRC_OBJS) -o $(NAME)
					@echo "$(NAME) created"

clean:
			@$(RM) $(SRC_OBJS)
			@echo "$(NAME) .o deleted"

fclean:			clean
				@$(RM) $(NAME) 
				@echo "$(NAME) deleted"

re:			fclean all

.PHONY:			all clean fclean re
