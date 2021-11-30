NAME		=	philo

SRC_FILES	=	src/main.c \
				src/errors/errors_1.c \
				src/utils/utils_libft.c \

INCLUDE_PATH	=	include/

SRC_OBJS	=	$(SRC_FILES:.c=.o)

CC		=	clang

CFLAGS		=	-Wall -Wextra -Werror -I$(INCLUDE_PATH) -g -pthread -fsanitize=address

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
