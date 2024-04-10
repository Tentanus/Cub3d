# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:      :+:           #
#                                                      +:+                     #
#    By: mweverli <mweverli@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2024/02/05 18:12:58 by mweverli      #+#    #+#                  #
#    Updated: 2024/02/06 11:26:56 by mweverli         ###     odam.nl          #
#                                                                              #
# **************************************************************************** #

#========================================#
#=========  GENERAL VARIABLES:  =========#
#========================================#

NAME			:=	cub3D

OBJ_DIR			:=	OBJ
SRC_DIR			:=	src
INC_DIR			:=	inc
LIB_DIR			:=	lib

SRC				:=	\
					main.c							\
					error/error.c					\
					minimap/minimap_hook.c			\
					minimap/minimap_player.c		\
					minimap/minimap_utils.c			\
					parser/check_path.c				\
					parser/get_data.c				\
					parser/get_data_utils.c			\
					parser/get_map.c				\
					parser/parser.c					\
					parser/parse_map.c				\
					raycaster/mlx_funcs.c			\
					raycaster/raycaster.c			\
					utils/logprinter.c				\
					utils/free_info.c				\


OBJ				:=	$(SRC:%.c=$(OBJ_DIR)/%.o)
SRC				:=	$(SRC:%=$(SRC_DIR)/%)
DEP				:=	$(OBJ:.o=.d)
DIR_LIST		:=	$(sort $(dir $(OBJ)))

-include $(DEP)

DIR_FT			:=	$(LIB_DIR)/libft
LIB_FT			:=	$(DIR_FT)/libft.a
DIR_MLX			:=	$(LIB_DIR)/MLX42
LIB_MLX			:=	$(DIR_MLX)/build/libmlx42.a

# DEFAULT_MAP := map/empty.cub
# DEFAULT_MAP := map/3x3.cub
# DEFAULT_MAP := map/6x6.cub
DEFAULT_MAP := map/err_test.cub

#============= COMPILATION ==============#

INCLUDE			:=	-I $(INC_DIR)					\
					-I $(DIR_FT)/include			\
					-I $(DIR_MLX)/include/MLX42		\
					-I $(DIR_MLX)/include

LIB_FLAG		:=	-ldl -lglfw -lm

CC				:=	cc
# CFL				:=	-Wall -Werror -Wextra -Wpedantic -Wfatal-errors
CFL				:=	-Wall -Wextra -Wpedantic -Wfatal-errors

ifdef DEBUG
CFL				+=	-g -fstandalone-debug
endif

ifndef NOLOG
CFL				+=	 -D LOG=1
endif

ifdef FSAN
CFL				+=	 -fsanitize=address,undefined
endif

COMPILE			:=	$(CC) $(CFL)

INFO_FL			:=											\
$(if $(findstring -g,$(CFL)),-g)							\
$(if $(findstring LOG,$(CFL)),LOG)							\
$(if $(findstring address,$(CFL)),addr)						\
$(if $(findstring undefined,$(CFL)),undef)					\

RM				:= rm -rf

#========================================#
#============== RECIPIES  ===============#
#========================================#

all: $(DIR_LIST)
	$(MAKE) $(NAME) -j4

$(DIR_LIST):
	@mkdir -p $@

$(NAME): $(LIB_MLX) $(LIB_FT) $(OBJ)
	@echo ""
	@echo "$(COMPILE) $(LIB_FLAG) $(GREEN)$(INCLUDE) $(CYAN)$(notdir $(OBJ)) $(BLUE)$(LIB_MLX) $(LIB_FT) $(ORANGE)-o $(NAME)$(RESET)"
	@$(COMPILE) $(LIB_FLAG) $(INCLUDE) $(OBJ) $(LIB_MLX) $(LIB_FT) -o $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@echo "$(CYAN)COMPILE $(INFO_FL) $(notdir $<)$(RESET)"
	@$(COMPILE) $(INCLUDE) -MMD -D NAME=\"$(NAME)\" -o $@ -c $<

clean:
	@echo "$(RED)$(BOLD)CLEANING $(NAME)$(RESET)"
	@$(RM) $(OBJ_DIR)

lclean:
	@$(RM) $(DIR_MLX)/build
	@$(MAKE) fclean -C $(DIR_FT)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

echo:
	@echo $(SRC) "\n"

run: all
	./$(NAME) $(DEFAULT_MAP)
#========================================#
#============== LIBRARIES ===============#
#========================================#

$(LIB_MLX):
	cmake$(if $(DEBUG), -DDEBUG=1) $(DIR_MLX) -B $(DIR_MLX)/build
	cmake --build $(DIR_MLX)/build

$(LIB_FT):
	$(MAKE) -C $(DIR_FT)

#========================================#
#============ MISCELLANEOUS =============#
#========================================#

.PHONY: all clean fclean re echo run 

.DEFAULT_GOAL := all

#=============== COLOURS ================#

OS		:=	$(shell uname -r)

ifneq ($(OS), 6.3.6-arch1-1)
	BOLD	:= \033[1m
	RED		:= \033[31;1m
	GREEN	:= \033[32;1m
	ORANGE	:= \033[33;1m
	BLUE	:= \033[34;1m
	CYAN	:= \033[36;1m
	RESET	:= \033[0m
endif
