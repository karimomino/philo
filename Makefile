# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kamin <kamin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 15:48:31 by kamin             #+#    #+#              #
#    Updated: 2022/05/24 18:02:09 by kamin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

INCLUDES	=	includes

DIR_S		=	./src/

SRC		=	main.c \
			errors.c \
			utils.c \
			number_check.c \
			output.c \
			philo.c \
			thread_manipulation.c \
			operations.c \
			time.c \
			monitor.c \
			mutex.c \
			fork_handler.c \

OBJS	=	$(addprefix $(DIR_S),$(SRC:.c=.o))

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra -g3 -pthread

RED=\033[0;31m

GREEN=\033[1;32m

NC=\033[0m

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CFLAGS += -pthread
endif


$(NAME): $(OBJS)
		@echo "✅${GREEN}The Previous Objects Have Been Updated${NC}"
		@$(CC) $(CFLAGS) $(OBJS) -I$(INCLUDES) -o $(NAME)
		@echo "✅${GREEN}./philo up to date${NC}"

all:	$(NAME)

clean:
		@rm -f $(OBJS)
		@echo "❌${RED}objects cleaned${NC}"

fclean: clean
		@rm -f $(NAME)
		@echo "❌${RED}executable ./philocleaned${NC}"

re:		fclean all
