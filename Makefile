# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emarin <emarin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/06 15:40:25 by emarin            #+#    #+#              #
#    Updated: 2019/08/20 14:17:44 by emarin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= scop
C		= gcc

FLAGS	= -Wall -Wextra -Werror

SRC_PATH	= src
INC_PATH	= include

OBJ_PATH	= obj

SRC		=	main.c \
			opengl_tools.c \
\
			geometry/matrix.c \
			geometry/matrix_op.c \
			geometry/matrix_op_2.c \
			geometry/projection_mt.c \
			geometry/vector_m.c \
			geometry/vector.c \
			geometry/vector_op.c \
			geometry/vector_op_2.c \
			geometry/utils.c \
			geometry/camera.c \
\
			shader/shader.c \
\
			utils/tga.c \
			utils/tga_read.c \

HEAD	=	define.h \
			scop.h \
			tga.h \
			geometry.h

OBJ		= $(SRC:.c=.o)

HEADP	= $(addprefix $(INC_PATH)/, $(HEAD))
OBJP	= $(addprefix $(OBJ_PATH)/, $(OBJ))
INCP	= $(foreach dir, $(INC_PATH), -I $(dir))

INCP_BREW = -I ~/.brew/include

LIBS_FLAGS = -L ~/.brew/lib -framework OpenGL -lglfw

NORMAL = "\x1B[0m"
RED = "\x1B[31m"
GREEN = "\x1B[32m"
YELLOW = "\x1B[33m"
BLUE = "\x1B[34m"
MAGENTA = "\x1B[35m"
CYAN = "\x1B[36m"
WHITE = "\x1B[37m"
BOLD = "\e[1m"
LIGHT = "\e[2m"
ITALIC = "\e[3m"
ULINE = "\e[4m"

all: $(NAME)

$(NAME): $(OBJ_PATH) $(OBJP)
	@printf $(CYAN)"-> create program : $(NAME)\n"$(NORMAL)
	@$(C) $(FLAGS) -o $(NAME) $(OBJP) $(LIBS_FLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADP)
	@printf $(YELLOW)"-> $<\n"$(NORMAL)
	@$(C) $(FLAGS) -c $< -o $@ $(INCP) $(INCP_BREW)

$(OBJ_PATH):
	@mkdir -p $(dir $(OBJP))

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)

re:
	@make fclean
	@make all

.PHONY: all re clean fclean
