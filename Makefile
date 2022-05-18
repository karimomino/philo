# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 15:48:31 by kamin             #+#    #+#              #
#    Updated: 2022/05/18 20:53:21 by kamin            ###   ########.fr        #
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

OBJS	=	$(addprefix $(DIR_S),$(SRC:.c=.o))

CC		=	gcc

FLAGS	=	-Wall -Werror -Wextra -g3 -lpthread

RED=\033[0;31m

GREEN=\033[1;32m

NC=\033[0m

$(NAME): $(OBJS)
		@echo "✅${GREEN}The Previous Objects Have Been Updated${NC}"
		@$(CC) $(FLAGS) $(OBJS) -I$(INCLUDES) -o $(NAME)
		@echo "✅${GREEN}./philo up to date${NC}"

all:	$(NAME)

clean:
		@rm -f $(OBJS)
		@echo "❌${RED}objects cleaned${NC}"

fclean: clean
		@rm -f $(NAME)
		@echo "❌${RED}executable ./philocleaned${NC}"

re:		fclean all
