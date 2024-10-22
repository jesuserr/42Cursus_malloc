# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 13:57:10 by jesuserr          #+#    #+#              #
#    Updated: 2024/10/22 13:13:24 by jesuserr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

LIBFT_DIR = libft/

NAME = libft_malloc_$(HOSTTYPE).so
LINK_NAME = libft_malloc.so
SRCS = malloc.c free.c inits.c show_alloc_mem.c realloc.c calloc.c log.c
PATH_SRCS = ./srcs/
PATH_OBJS = ./srcs/objs/
PATH_DEPS = ./srcs/objs/

OBJS = $(addprefix $(PATH_OBJS), $(SRCS:.c=.o))
DEPS = $(addprefix $(PATH_DEPS), $(SRCS:.c=.d))

INCLUDE = -I./ -I./libft/includes/
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g -fPIC -pedantic -Wshadow

NORM = $(addprefix $(PATH_SRCS), $(SRCS)) #$(PATH_SRCS)malloc.h
GREEN = "\033[0;92m"
RED = "\033[0;91m"
BLUE = "\033[0;94m"
NC = "\033[37m"

all: makelibft $(NAME)

makelibft:
	@make --no-print-directory -C $(LIBFT_DIR)	
	@echo ${GREEN}"Libft Compiled!\n"${NC};

$(PATH_OBJS)%.o: $(PATH_SRCS)%.c Makefile
	@mkdir -p $(PATH_OBJS)
	$(CC) $(CFLAGS) -MMD $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_DIR)libft.a
	$(CC) -shared $(CFLAGS) $(OBJS) $(LIBFT_DIR)libft.a -o ${NAME}
	@ln -sf ${NAME} ${LINK_NAME}
	@echo ${GREEN}"${NAME} Compiled!\n"${NC};
-include $(DEPS)

clean:
	@make clean --no-print-directory -C $(LIBFT_DIR)
	@rm -rf $(PATH_OBJS)	
		
fclean:
	@make fclean --no-print-directory -C $(LIBFT_DIR)
	@rm -rf $(PATH_OBJS)
	$(RM) $(NAME) ${LINK_NAME}

norm:
	@echo ${BLUE}"\nChecking Norminette..."${NC}
	@if norminette $(NORM); then echo ${GREEN}"Norminette OK!\n"${NC}; \
	else echo ${RED}"Norminette KO!\n"${NC}; \
	fi

re: fclean all

.PHONY: all clean fclean re makelibft norm