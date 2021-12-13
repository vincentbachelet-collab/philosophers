NAME		=	philo

SRC_FILES	=	src/main.c \
				src/errors/errors_1.c \
				src/utils/utils_libft.c \
				src/utils/status_philo_and_threads.c  \
				src/utils/thread_create_and_init.c \
				src/free/free.c \

INCLUDE_PATH	=	include/

SRC_OBJS	=	$(SRC_FILES:.c=.o)

CC		=	clang

CFLAGS		=	-Wall -Wextra -Werror -I$(INCLUDE_PATH) -g -pthread -fsanitize=thread

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
