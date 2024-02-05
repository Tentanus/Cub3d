# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mweverli <mweverli@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2024/02/05 18:12:58 by mweverli      #+#    #+#                  #
#    Updated: 2024/02/05 18:29:55 by mweverli      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#========================================#
#=========  GENERAL VARIABLES:  =========#
#========================================#

NAME			:=	Cub3d

OBJ_DIR			:=	OBJ
SRC_DIR			:=	src
INC_DIR			:=	inc
LIB_DIR			:=	lib

SRC				:=	\
					main.c			\


OBJ				:=	$(SRC:%.c=$(OBJ_DIR)/%.o)
SRC				:=	$(SRC:%=$(SRC_DIR)/%)
DEP				:=	$(OBJ:.o=.d)
DIR_LIST		:=	$(sort $(dir $(OBJ)))

-include $(DEP)

DIR_FT			:=	$(LIB_DIR)/libft
LIB_FT			:=	$(DIR_FT)/libft.a
DIR_MLX			:=	$(LIB_DIR)/MLX42
LIB_MLX			:=	$(DIR_MLX)/build/libmlx42.a

#============= COMPILATION ==============#

INCLUDE			:=	-I $(INC_DIR)					\
					-I $(DIR_FT)/include			\
					-I $(DIR_MLX)/include/MLX42

CC				:=	cc
CFL				:=	-Wall -Werror -Wextra -Wpedantic -Wfatal-errors

ifdef DEBUG
CFL				+=	-g -fstandalone-debug
endif

ifdef LOG 
CFL				+=	 -D LOG=Cub3d.log
endif

ifdef FSAN
CFL				+=	 -fsanitize=address,undefined
endif

COMPILE			:=	$(CC) $(CFL)

INFO_FL			:=											\
$(if $(findstring -g,$(CFL)),-g)							\
$(if $(findstring address,$(CFL)),addr)						\
$(if $(findstring undefined,$(CFL)),undef)					\

RM				:= rm -rf

#========================================#
#============== RECIPIES  ===============#
#========================================#

all: $(DIR_LIST) $(NAME)

$(DIR_LIST):
	@mkdir -p $@

$(NAME): $(LIB_MLX) $(LIB_FT) $(OBJ)
	@echo ""
	@echo "$(COMPILE) $(GREEN)$(INCLUDE) $(CYAN)$(notdir $(OBJ))$(RESET) $(LIB_MLX) $(LIB_FT) -o $(NAME)"
	@$(COMPILE) $(INCLUDE) $(OBJ) $(LIB_MLX) $(LIB_FT) -o $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@echo "$(CYAN)COMPILE $(INFO_FL) $(notdir $(<:%.c=%))$(RESET)"
	@$(COMPILE) $(INCLUDE) -MMD -o $@ -c $< 

clean:
	@echo "$(RED)$(BOLD)CLEANING $(NAME)$(RESET)"
	$(RM) $(OBJ_DIR)

fclean: clean 
	$(RM) $(NAME)
	$(RM) $(DIR_MLX)/build
	@$(MAKE) fclean -C $(DIR_FT)

re: fclean all

echo:
	@echo $(SRC) "\n"

#========================================#
#============== LIBRARIES ===============#
#========================================#

$(LIB_MLX):
	cmake $(if $(findstring -g,$(CFL)),-DDEBUG=1) $(DIR_MLX) -B $(DIR_MLX)/build
	cmake --build $(DIR_MLX)/build

$(LIB_FT):
	$(MAKE) -C $(DIR_FT)

#========================================#
#============ MISCELLANEOUS =============#
#========================================#

.PHONY: all clean fclean re echo 

.DEFAULT_GOAL := all

#=============== COLOURS ================#

OS		:=	$(shell uname -r)

ifneq ($(OS), 6.3.6-arch1-1)
	BOLD	:= \033[1m
	RED		:= \033[31;1m
	GREEN	:= \033[32;1m
	CYAN	:= \033[36;1m
	RESET	:= \033[0m
endif