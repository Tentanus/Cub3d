# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mweverli <mweverli@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/14 18:12:58 by mweverli      #+#    #+#                  #
#    Updated: 2023/09/04 17:29:55 by mweverli      ########   odam.nl          #
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
					main.c

OBJ				:=	$(SRC:%.cpp=$(OBJ_DIR)/%.o)
SRC				:=	$(SRC:%=$(SRC_DIR)/%)
DEP				:=	$(OBJ:.o=.d)
DIR_LIST		:=	$(sort $(dir $(OBJ)))

-include $(DEP)

DIR_FT			:=	$(LIB_DIR)/libft
LIB_FT			:=	$(DIR_FT)/libft.a
DIR_MLX			:=	$(LIB_DIR)/MLX42
#LIB_MLX			:=	$(DIR_FT)/

#============= COMPILATION ==============#

INCLUDE			:=	-I $(INC_DIR)

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

all: $(LIB_MLX) $(LIB_FT) $(DIR_LIST) $(NAME)

$(DIR_LIST):
	@mkdir -p $@

$(NAME): $(OBJ)
	@echo ""
	@$(COMPILE) $(INCLUDE) $(OBJ) -o $(NAME)
	@echo "$(COMPILE) $(INCLUDE) $(CYAN)$(notdir $(OBJ))$(RESET) -o $(NAME)"

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp
	@$(COMPILE) $(INCLUDE) -MMD -o $@ -c $< 
	@echo "$(CYAN)COMPILE $(INFO_FL) $(notdir $(<:%.c=%))$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)$(BOLD)CLEANING $(NAME)$(RESET)"

fclean: clean 
	@$(RM) $(NAME)
	@$(RM) $(DIR_MLX)/build
	@$(MAKE) fclean -C $(DIR_FT)

re: fclean all

echo:
	@echo $(SRC) "\n"

#========================================#
#============== LIBRARIES ===============#
#========================================#

$(LIB_MLX):
	cmake $(DIR_MLX) -B $(DIR_MLX)/build
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
