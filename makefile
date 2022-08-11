# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/05 18:30:54 by mmardi            #+#    #+#              #
#    Updated: 2022/08/11 21:52:57 by mmardi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = CUB3D

CFLAGS = -Wall -Wextra -Werror

FILES = main.c get_next_line.c get_next_line_utils.c

OBJ = $(FILES:.c=.o)

HEADER =  raycast.h

all: $(NAME)
$(NAME) : $(HEADER) $(OBJ)
	@$(CC) $(CFLAGS) $(FILES)  -lmlx -framework OpenGL -framework AppKit  min/libmlx.a -o  $(NAME)

clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(OBJ) $(NAME)
re: fclean all