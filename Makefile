# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 18:05:45 by rmouhoub          #+#    #+#              #
#    Updated: 2023/08/21 13:45:40 by rmouhoub         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex

LIBFT			=	libft.a

DIR_SRCS		=	srcs/mandatory
DIR_OBJS		=	objs

DIR_PARSING		=	parsing


SRCS_NAMES 		= 	$(DIR_PARSING)/parsing.c \
					$(DIR_PARSING)/init.c \
					$(DIR_PARSING)/open_utils.c \
					$(DIR_PARSING)/exec_utils.c \
					

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))
OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

CFLAGS			= -Wall -Werror -Wextra -g3

CC				=	cc

HEAD			= -Iincludes -Ilibft 

all				:	${NAME}

$(NAME): $(OBJS)
	make -C libft
	mv libft/libft.a .
	$(CC) -g3 $(OBJS) $(CFLAGS) ${HEAD} ${LIBFT}  -o $(NAME)
	@echo "\033[34;5mPipex\033[0m"

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)
	mkdir -p objs/parsing
	mkdir -p objs/init
	mkdir -p objs/open_utils
	mkdir -p objs/exec_utils
	
$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c | $(DIR_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEAD)





clean			:
					make clean -C libft
					rm -rf ${OBJS} 

fclean			:	clean
					make fclean -C libft
					rm -rf ${LIBFT}
					rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re bonus
