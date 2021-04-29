# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/16 17:26:10 by ede-thom          #+#    #+#              #
#    Updated: 2021/04/29 16:48:08 by ede-thom         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	src/minishell.c\
				src/msh_prompt.c\
				src/msh_parsing.c\
				src/msh_parsing2.c\
				src/msh_parsing3.c\
				src/msh_parsing4.c\
				src/msh_parsing5.c\
				src/msh_parsing6.c\
				src/builtin/common.c\
				src/msh_execute.c\
				src/msh_execute2.c\
				src/msh_redirector.c\
				src/msh_variables.c\
				src/msh_variables2.c\
				src/utils.c\
				src/msh_error.c\
				src/char_array.c

SRCS		+=	src/gnl/get_next_line.c\
				src/gnl/get_next_line_utils.c

# Built-In's

SRCS		+= 	src/builtin/exit.c\
				src/builtin/echo.c\
				src/builtin/env.c\
				src/builtin/pwd.c\
				src/builtin/cd.c\
				src/builtin/unset.c\
				src/builtin/export.c

MKDIR_P		=	mkdir -p
RM			=	rm -f

NAME		=	minishell

# **************************************************************************** #

# Directories
SRC_DIR		=	src
OBJ_DIR		=	obj
INC_DIR		=	include
# **************************************************************************** #

# LIBFT
LFT_NAME	=	libft.a
LFT_PATH	=	./libft
LFT_LIB		=	-L$(LFT_PATH) -lft
LFT_INC		=	-I$(LFT_PATH)/
LFT_RULE	=	$(LFT_PATH)/$(LFT_NAME)
# **************************************************************************** #

OBJS		=	$(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJS_NODIR	=	$(patsubst %.o, $(OBJ_DIR)/%.o, $(notdir $(OBJS)))

LIB			=	$(LFT_LIB) -lncurses
INC			=	-I $(INC_DIR) $(LFT_INC)

# COLORS
RED			=	\033[0;31m
GREEN		= 	\033[0;32m
YELLOW		=	\033[0;33m
BLUE		=	\033[0;34m
MAGENTA		=	\033[0;35m
CYAN		=	\033[0;36m
RESET		=	\033[0m
# **************************************************************************** #
CFLAGS		=	-Wall -Wextra -Werror -g

CC			=	clang


all:			${NAME}

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(INC_DIR)/
				@$(MKDIR_P) $(OBJ_DIR)
				@$(CC) $(CFLAGS) -c -o $(OBJ_DIR)/$(notdir $@) $< $(INC)
				@printf "$(CYAN)Compiling $(MAGENTA)$<$(RESET)\r"
				@printf "\r                                                                                                                                \r"


# $(SRC_DIR)/%.c:	$(OBJ_DIR)/$(notdir %.o) $(INC_DIR)
# 				@$(MKDIR_P) $(OBJ_DIR)
# 				@$(CC) $(CFLAGS) -c -o $< $@ $(INC)
# 				@printf "$(CYAN)Compiling $(MAGENTA)$<$(RESET)\r"

$(NAME):		$(LFT_RULE) $(OBJS)
				@printf "$(CYAN)Done creating $(NAME) object files!\n$(RESET)"
				@$(CC) $(CFLAGS) $(OBJS_NODIR) -o $@ $(INC) $(LIB)
				@echo "$(CYAN)Created $(GREEN)$(NAME)$(CYAN)!! $(RESET)"

$(LFT_RULE):
				@make -C $(LFT_PATH)/

clean: 
				@${RM} ${OBJS_NODIR}
				@$(MKDIR_P) $(OBJ_DIR)
				@rmdir -p $(OBJ_DIR)
				@echo "$(CYAN)CLEANING$(RESET)"

fclean:			clean
				@${RM} ${NAME}
				@make -C $(LFT_PATH) fclean
				@echo "$(CYAN)Everything is $(RED)c $(YELLOW)l $(GREEN)e $(CYAN)a $(MAGENTA)n $(RESET)"
				
re:				clean all

re-libft:		
				@make -C $(LFT_PATH)

bonus:			all

good:			all
				./$(NAME)

together:		all
				@echo "$(CYAN)"
				@echo "&&&&&&&&&&&&&&&(((((((((((((#((((((((((((((((((((((((((((((((((((((((((((((((%@@@@@@@@@@@@@%#######%&&&&&&&&&"
				@echo "&&&&&&&&&&&&&&%(((#(((((((((((#((((((((##(((((((((((((((((((((((((((((((((((((((&@@@@@@@@@@@@@@@@%####&&&@&&&"
				@echo "&&&&&&&&&&&&@@@@@@@%((#((((((#(((((((((#(((((((((((((((((((%@@@((((((((((((((((@@&@@@@@@@@@@@@@@@@@%#&&&@@&&&"
				@echo "&&&&&&&&&&&@@@@@@@@@@@@@#((((#(((((((##((((((((((((#(#%@@@@@@@@@@@@((((((((((((#@@&@@@@@@@&@@@@@@@@@@@@@@@@@@"
				@echo "&&&&&&&&&@@@@@@@@@@@@@@@@@@@&((((((((%&((((((((#%@@@@@@@@@@@@@@@@@@@@@#(((((((((((&@@@@@@@@#((((((&@@@@@@@@@&"
				@echo "&&&&&&&&&@@@@@@@@@@@@@@@@@@@@&(#(((((&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%(((((((((((@@@@@@@%((((((((&@@@@@@@@@"
				@echo "&&&&&&&&&&((((((((((%@@@@@@@@@@#((((((@@@@@@@@@@@@@@@@@@@@@@%%#((#%@@@@@##((((((((((@@@@@%((((((#((#@@@@@@@@@"
				@echo "&&&&&&&&&&(((((((((((((#&@@@@@#((((@@@@@@@@@@@@@@%(#%%##((((((((#&@@@(((((((((#(#@@@&(#((((%((((&@@@@@@@@@&&@"
				@echo "&&&&&&&&&&&(((((((((((((((#((@@@%(((((&@@@@@@(((##(((((((#(((((((((#@@(((((((((((&@&((((((#(((((%@@@@@@@@@@@@"
				@echo "&&&&&&&&&&&&&%(#(((((((((###(((##(##(((((((((((((##(((((((((((##(((((((((&%(((((((((((@((((((##(((((%@@@@@@@@"
				@echo "&&&&&&&&&&&&&&%(((((((((##((((((((##((((((((((((#(((((((((((((((#((((((((((((((((((((((((((((#((((((%@@&@@@@@"
				@echo "&&&&&&&&&&&&&&&%(((((((#((#((((((((#(((((((((((((((((((((((((((((((((((((((((((((((((((((((((#(((((#@@@@&@@@@"
				@echo "&&&&&&&&&&&&&&&&&((((#((((((((((((##((((((((((((((((((((((((((((((###(((((((((((((((((((((((((((((#@@@@@&@@@@"
				@echo "&&&&&&&&&&&&&&(((((((((((((((((((#(((((((((((((((#(###%&@@@@@@#(##(((((((((((((((((((((((((((((#@@@@@@&@@@@&&"
				@echo "&&&&&&&&&&&%#((((((@@@@&&&@@@@@@@%/#(((((((((((#(*******(@@@@@(((((((((((((((((((((((((##(((((%@@@@@@@@@@@@@&"
				@echo "&&&&&&&&%#((((((((((((#(******@@@%##((((((((((#((((((((((((((((((((((((((((((((((((((((((###(##(#@@@@@@@@@@@@"
				@echo "&&&&&&&%((((((((((((#(#((***(((((((%(((((((((((##(((((((((((((((((((((((((((((((((((((((((#((((((@@@@@@@@&@@@"
				@echo "&&&&&&&&%(((((((((((((##(((((((((#(#((((((((((((((#((((((((((((((((((((((((((((((((((((((((%(((((&@@@@@@@@&@@"
				@echo "&&&&&&&&&%((((((((((((((((((((((((##((((((((((((((((((((((((((((((((((((((((((((((((((((((((#((((#@@@@@@@@@@&"
				@echo "&&&&&&&&&&%((((((((((((((((((((((((#((((((((((((((((((((((((((((((((((((((((((((((((((((((((#(((((&@@@@@@@@@@"
				@echo "&&&&&&&&&&&%(((((((((((((((((((((((#((((((((((((((((((((((((((((((###(((((((((((((((((((((((#%((((#@@@@@@@@@@"
				@echo "&&&&&&&&&&&((((((((((((((((((((((#((((((((((((((((((((((((((((##(((#((((((((((((((((((((((((#((((&@@@@@@@@@@@"
				@echo "&&&&&&&&&&&&(((((((((((((((((((((#((((((((#((((((((((((#(#%#(###(((%#(((((((((((((((((((((((#((((#@@@@@@@@@@@"
				@echo "&&&&&&&&&&&&&((((((((((((((((((#(#(((((((#(%((((((((((((((((((##(((##(((((((((((((((((((((((#%((((&@@@@@@@@@@"
				@echo "&&&&&&&&&&&&&&&(((((((((((((((#((#(#((((((((((%#(((((((((((((((#%((((#((((((((((((((((((((((((((#(((#@@@@@@@@"
				@echo "&&&&&&&&&&&&&&&%((((((((((((((#(#((#(((((((((((%((((((((((((((#%(((((((((((((((((((((((((((((((((#(((&@@@@@@@"
				@echo "&&&&&&&&&&&&&&&&%(((((((((((((((#(#%(((((((######((((((((((((%%#(((((((((((((((((((((((((((((((((#(#(#@@@@@@@"
				@echo "&&&&&&&&&&&&&&&&((((((((((((((((##(((((((##((((((((((((((#(%#(((((((((((((((((((((((((((((((((((%(((%@@@@@@@@"
				@echo "&&&&&&&&&&&&&&&&&((((((((((((((((#((((((##((((((((((((((#*(#(((((((((((((((((((((((((((((((((((((#((#@@@@@@@@"
				@echo "&&&&&&&&&&&&&&&&&&&((((((((((((((((#((((((##((((((((((((%**((((((((((((((((((((((((((((((((((((((((##((%@@@@@"
				@echo "&&&&&&&&&&&&&&&&&@@#((((((((((((((((#(((((##((((((((###/**%(#(((((((((((((((((((((((((((((((((((((((#((#@@@@@"
				@echo "&&&&&&&&&&&&&&&&@@@%(((((((((((((##(((((((((((((#(##****/#(((((((((((((((((((((((((((((((((((((((((((%((%@@@@"
				@echo "&&&&&&&&&&&&&&&@@@@@#((((((((((#############%#/********#(((((((((((((((((((((((((((((((((((((((((((((%((#@@@@"
				@echo "&&&&&&&&&&&&&&@@@@@@#(((((((((((********************/#((((((((((((((((((((((((((((((((((((((((((((###((((%@@@"
				@echo "&&&&&&&&&&&&&@@@@@@@#(((####((((/***************/(#((((((((((((((((((((((((((((((((((((((((((((((##((((((#@@@"
				@echo "&&&&&&&&&&&&@@@@@@@@#((((%(#((((((#############((((((((((((((((((((((((((((((((((((((((((((((((#%(((((((((%@@"
				@echo "&&&&&&&&&&&@@@@@@@@@((((((%(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((%((((((((((((&@"
				@echo "&&&&&&&&&&&@@@@@@@@&(((((((#((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((##(((((((((((((#@"
				@echo "&&&&&&&&&&&@@@@@@@@%(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((#(%((((((((((((((((&"
				@echo "&&&&&&&&&&&@@@@@@@@#(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((%((((((((((((((((((#"
				@echo "&&&&&&&&&&&@@@@@@@@((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((##(((((((((((((((((((("
				@echo "&&&&&&&&&&&@@@@@@@#((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((#%(((((((((((((((((((((("
				@echo "&&&&&&&&&&@@@@@@@&((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((#(((((((((((((((((((((((("
				@echo "&&&&&&&&&@@@@@@@@#((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((##((((((((((((((((((((((((("
				@echo "$(RESET)"
				@echo "$(YELLOW)╔═╗┬ ┬  ┬ ┬┌─┐┌─┐┬ ┬    ┬┌┬┐┌─┐  ┌─┐┬  ┬    ┌─┐┌─┐┌┬┐┬┌┐┌┌─┐  ┌┬┐┌─┐┌─┐┌─┐┌┬┐┬ ┬┌─┐┬─┐$(RESET)"
				@echo "$(YELLOW)║ ║├─┤  └┬┘├┤ ├─┤├─┤    │ │ └─┐  ├─┤│  │    │  │ │││││││││ ┬   │ │ ││ ┬├┤  │ ├─┤├┤ ├┬┘$(RESET)"
				@echo "$(YELLOW)╚═╝┴ ┴   ┴ └─┘┴ ┴┴ ┴┘,  ┴ ┴ └─┘  ┴ ┴┴─┘┴─┘  └─┘└─┘┴ ┴┴┘└┘└─┘   ┴ └─┘└─┘└─┘ ┴ ┴ ┴└─┘┴└─$(RESET)"

.PHONY:	all clean fclean test re
