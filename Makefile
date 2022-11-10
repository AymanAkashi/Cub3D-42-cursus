# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 09:41:31 by moseddik          #+#    #+#              #
#    Updated: 2022/11/10 07:36:39 by aaggoujj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# *********************************** Colors ***********************************
NC				:= \033[m
RED				:= \033[0;31m
GREEN			:= \033[1;32m
YELLOW			:= \033[1;33m
BLUE			:= \033[0;34m
PURPLE			:= \033[1;35m
CYAN			:= \033[1;36m

# ******************************** Directories *********************************
INC_DIR			:= include
SRC_DIR			:= src
OBJ_DIR			:= obj
LIB_DIR			:= lib
LIBFT_DIR		:= $(LIB_DIR)/libft
MLX_DIR			:= $(LIB_DIR)/MLX

# *********************************** Files ************************************
NAME			:= cub3d
SRC				:= main.c \
					get_next_line.c \
					get_next_line_utils.c \
					coloring_output.c \
					list_compass.c \
					cub_tools.c \
					parsing.c \
					parsing_error.c \
					parsing_tools.c \
					parsing_color.c \
					parsing_tools_2.c \
					parsing_map.c	\
					parsing_map2.c	\
					free_data.c \
					init_data.c \
					begin_cub.c \
					keypress.c \
					hook.c \
					render.c \
					player_draw.c \
					list_door.c \
					handling_doors.c \
					rays_casting.c 
OBJ				:= $(SRC:.c=.o)
INC				:= $(shell ls $(INC_DIR))
LIBFT			:= libft.a
MLX 			:= libmlx.a
LIBFT_SRC		:= $(shell ls $(LIBFT_DIR)/$(SRC_DIR))
LIBFT_INC		:= libft.h

# ****************************** Compiler Options ******************************
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -Imlx -g #-fsanitize=address
INCFLAGS		:= -I $(INC_DIR) -I $(LIBFT_DIR)/$(INC_DIR)
LIBFLAGS		:= -L $(LIBFT_DIR) -lft

# ******************************* Other commands *******************************
RM				:= rm -rf
MKDIR			:= mkdir -p

# ******************************** Dependencies ********************************
OBJ_DEP			:= $(addprefix $(OBJ_DIR)/, $(OBJ))
INC_DEP			:= $(addprefix $(INC_DIR)/, $(INC))
LIBFT_DEP		:= $(LIBFT_DIR)/$(LIBFT)
MLX_DEP			:= $(MLX_DIR)/$(MLX)
LIBFT_SRC_DEP	:= $(addprefix $(LIBFT_DIR)/$(SRC_DIR)/, $(LIBFT_SRC))
LIBFT_INC_DEP	:= $(LIBFT_DIR)/$(INC_DIR)/libft.h

# ********************************** Targets ***********************************
all: $(NAME)

$(NAME): $(OBJ_DEP) $(INC_DEP) $(LIBFT_DEP) $(MLX_DEP)
	@echo "$(BLUE)Building	$(PURPLE)$(NAME)$(NC)"
	@$(CC) $(CFLAGS) $(LIBFLAGS) $(MLX_DEP) $(OBJ_DEP) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DEP)
	@$(MKDIR) $(OBJ_DIR)
	@echo "$(GREEN)Compiling	$(YELLOW)$(shell basename $<)$(NC)"
	@$(CC) $(CFLAGS) $(INCFLAGS) -c -o $@ $<

$(LIBFT_DEP): $(LIBFT_SRC_DEP) $(LIBFT_INC_DEP)
	@echo "$(BLUE)Building	$(CYAN)$(LIBFT)$(NC)"
	@make -C $(LIBFT_DIR)

$(MLX_DEP):
	@echo "$(BLUE)Building	$(CYAN)$(MLX)$(NC)"
	@make -C $(MLX_DIR) 2> /dev/null
clean:
	@echo "$(RED)Removing$(BLUE)	$(LIBFT)  Object files$(NC)"
	@make clean -C $(LIBFT_DIR)
	@echo "$(RED)Removing	$(YELLOW)Object files$(NC)"
	@$(RM) $(OBJ_DIR)
	@ make clean -C $(MLX_DIR)

fclean: clean
	@echo "$(RED)Removing	$(BLUE)$(LIBFT)$(NC)"
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)Removing	$(PURPLE)$(NAME)$(NC)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
