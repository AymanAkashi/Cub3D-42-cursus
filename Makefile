# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 09:41:31 by moseddik          #+#    #+#              #
#    Updated: 2022/10/16 22:40:59 by aaggoujj         ###   ########.fr        #
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
MLX42_DIR		:= $(LIB_DIR)/MLX42

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
					init_data.c 
OBJ				:= $(SRC:.c=.o)
INC				:= $(shell ls $(INC_DIR))
LIBFT			:= libft.a
MLX42			:= libmlx42.a
LIBFT_SRC		:= $(shell ls $(LIBFT_DIR)/$(SRC_DIR))
LIBFT_INC		:= libft.h

# ****************************** Compiler Options ******************************
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -g -fsanitize=address
INCFLAGS		:= -I $(INC_DIR) -I $(LIBFT_DIR)/$(INC_DIR) \
					-I $(shell brew --prefix glfw)/$(INC_DIR) \
					-I lib/MLX42/include/MLX42
LIBFLAGS		:= -L $(LIBFT_DIR) -lft \
					-L $(MLX42_DIR) -lmlx42 \
					-lglfw -L $(shell brew --prefix glfw)/lib

# ******************************* Other commands *******************************
RM				:= rm -rf
MKDIR			:= mkdir -p

# ******************************** Dependencies ********************************
OBJ_DEP			:= $(addprefix $(OBJ_DIR)/, $(OBJ))
INC_DEP			:= $(addprefix $(INC_DIR)/, $(INC))
LIBFT_DEP		:= $(LIBFT_DIR)/$(LIBFT)
MLX42_DEP		:= $(MLX42_DIR)/$(MLX42)
LIBFT_SRC_DEP	:= $(addprefix $(LIBFT_DIR)/$(SRC_DIR)/, $(LIBFT_SRC))
LIBFT_INC_DEP	:= $(LIBFT_DIR)/$(INC_DIR)/libft.h
MLX42_INC_DEP	:= $(MLX42_DIR)/$(INC_DIR)/MLX42

# ********************************** Targets ***********************************
all: $(NAME)

$(NAME): $(OBJ_DEP) $(INC_DEP) $(LIBFT_DEP) $(MLX42_DEP)
	@echo "$(BLUE)Building	$(PURPLE)$(NAME)$(NC)"
	@$(CC) $(CFLAGS) $(LIBFLAGS) $(OBJ_DEP) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DEP)
	@$(MKDIR) $(OBJ_DIR)
	@echo "$(GREEN)Compiling	$(YELLOW)$(shell basename $<)$(NC)"
	@$(CC) $(CFLAGS) $(INCFLAGS) -c -o $@ $<

$(LIBFT_DEP): $(LIBFT_SRC_DEP) $(LIBFT_INC_DEP)
	@echo "$(BLUE)Building	$(CYAN)$(LIBFT)$(NC)"
	@make -C $(LIBFT_DIR)

$(MLX42_DEP): $(MLX42_INC_DEP)
	@echo "$(BLUE)Building	$(CYAN)$(MLX42)$(NC)"
	@make -C $(MLX42_DIR)

clean:
	@echo "$(RED)Removing$(BLUE)	$(LIBFT)  Object files$(NC)"
	@make clean -C $(LIBFT_DIR)
	@echo "$(RED)Removing$(BLUE)	$(MLX42)  Object files$(NC)"
	@make clean -C $(MLX42_DIR)
	@echo "$(RED)Removing	$(YELLOW)Object files$(NC)"
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Removing	$(BLUE)$(LIBFT)$(NC)"
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)Removing	$(BLUE)$(MLX42)$(NC)"
	@make fclean -C $(MLX42_DIR)
	@echo "$(RED)Removing	$(PURPLE)$(NAME)$(NC)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
